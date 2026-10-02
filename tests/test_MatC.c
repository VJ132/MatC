#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/MatC.h"

static int tests_run = 0;
static int tests_passed = 0;

#define CHECK(condition)                                                        \
    do {                                                                        \
        ++tests_run;                                                            \
        if (!(condition)) {                                                     \
            fprintf(stderr, "FAIL: %s:%d: %s\n", __FILE__, __LINE__, #condition); \
            return 0;                                                           \
        }                                                                       \
        ++tests_passed;                                                         \
    } while (0)

static int mat_equals(const Matrix *matrix,
                      size_t rows,
                      size_t columns,
                      const int *expected) {
    if (matrix == NULL || matrix->rows != rows || matrix->columns != columns)
        return 0;

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            if (*matc_at(matrix, i, j) != expected[i * columns + j])
                return 0;
        }
    }

    return 1;
}

static Matrix *mat_from_array(size_t rows, size_t columns, const int *values) {
    Matrix *matrix = matc_allocate(rows, columns);
    if (matrix == NULL)
        return NULL;

    memcpy(matrix->data, values, sizeof(int) * rows * columns);
    return matrix;
}

static int test_allocate_and_access(void) {
    Matrix *matrix = matc_allocate(2, 3);
    CHECK(matrix != NULL);
    CHECK(matrix->rows == 2);
    CHECK(matrix->columns == 3);

    *matc_at(matrix, 0, 0) = 10;
    *matc_at(matrix, 0, 1) = 20;
    *matc_at(matrix, 0, 2) = 30;
    *matc_at(matrix, 1, 0) = 40;
    *matc_at(matrix, 1, 1) = 50;
    *matc_at(matrix, 1, 2) = 60;

    const int expected[] = {10, 20, 30, 40, 50, 60};
    CHECK(mat_equals(matrix, 2, 3, expected));

    matc_free(matrix);

    CHECK(matc_allocate(0, 3) == NULL);
    CHECK(matc_allocate(3, 0) == NULL);

    return 1;
}

static int test_fill(void) {
    Matrix *matrix = matc_allocate(3, 2);
    CHECK(matrix != NULL);

    matc_fill(matrix, 7);

    const int expected[] = {
        7, 7,
        7, 7,
        7, 7
    };

    CHECK(mat_equals(matrix, 3, 2, expected));
    matc_free(matrix);
    return 1;
}

static int test_sum(void) {
    const int a_values[] = {
        1, 2, 3,
        4, 5, 6
    };
    const int b_values[] = {
        6, 5, 4,
        3, 2, 1
    };
    const int expected[] = {
        7, 7, 7,
        7, 7, 7
    };

    Matrix *a = mat_from_array(2, 3, a_values);
    Matrix *b = mat_from_array(2, 3, b_values);
    Matrix *c = matc_allocate(2, 3);

    CHECK(a != NULL);
    CHECK(b != NULL);
    CHECK(c != NULL);

    matc_sum(c, a, b);
    CHECK(mat_equals(c, 2, 3, expected));

    matc_free(a);
    matc_free(b);
    matc_free(c);
    return 1;
}

static int test_sub(void) {
    const int a_values[] = {
        10, 20,
        30, 40
    };
    const int b_values[] = {
        1, 2,
        3, 4
    };
    const int expected[] = {
        9, 18,
        27, 36
    };

    Matrix *a = mat_from_array(2, 2, a_values);
    Matrix *b = mat_from_array(2, 2, b_values);
    Matrix *c = matc_allocate(2, 2);

    CHECK(a != NULL);
    CHECK(b != NULL);
    CHECK(c != NULL);

    matc_sub(c, a, b);
    CHECK(mat_equals(c, 2, 2, expected));

    matc_free(a);
    matc_free(b);
    matc_free(c);
    return 1;
}

static int test_mul_square(void) {
    const int a_values[] = {
        1, 2,
        3, 4
    };
    const int b_values[] = {
        5, 6,
        7, 8
    };
    const int expected[] = {
        19, 22,
        43, 50
    };

    Matrix *a = mat_from_array(2, 2, a_values);
    Matrix *b = mat_from_array(2, 2, b_values);
    Matrix *c = matc_allocate(2, 2);

    CHECK(a != NULL);
    CHECK(b != NULL);
    CHECK(c != NULL);

    matc_mul(c, a, b);
    CHECK(mat_equals(c, 2, 2, expected));

    matc_free(a);
    matc_free(b);
    matc_free(c);
    return 1;
}

static int test_mul_rectangular(void) {
    /* (3 x 2) * (2 x 3) = (3 x 3) */
    const int a_values[] = {
        1, 2,
        3, 4,
        5, 6
    };
    const int b_values[] = {
         7,  8,  9,
        10, 11, 12
    };
    const int expected[] = {
        27, 30, 33,
        61, 68, 75,
        95, 106, 117
    };

    Matrix *a = mat_from_array(3, 2, a_values);
    Matrix *b = mat_from_array(2, 3, b_values);
    Matrix *c = matc_allocate(3, 3);

    CHECK(a != NULL);
    CHECK(b != NULL);
    CHECK(c != NULL);

    matc_mul(c, a, b);
    CHECK(mat_equals(c, 3, 3, expected));

    matc_free(a);
    matc_free(b);
    matc_free(c);
    return 1;
}

static int test_mul_with_ones_and_zeros(void) {
    const int ones[] = {
        1, 1, 1,
        1, 1, 1
    };
    const int zeros[] = {
        0, 0,
        0, 0,
        0, 0
    };
    const int expected[] = {
        0, 0,
        0, 0
    };

    Matrix *a = mat_from_array(2, 3, ones);
    Matrix *b = mat_from_array(3, 2, zeros);
    Matrix *c = matc_allocate(2, 2);

    CHECK(a != NULL);
    CHECK(b != NULL);
    CHECK(c != NULL);

    matc_mul(c, a, b);
    CHECK(mat_equals(c, 2, 2, expected));

    matc_free(a);
    matc_free(b);
    matc_free(c);
    return 1;
}

static int test_scale(void) {
    const int values[] = {
        1, -2,
        3,  4
    };
    const int expected_positive[] = {
         3, -6,
         9, 12
    };
    const int expected_zero[] = {
        0, 0,
        0, 0
    };
    const int expected_negative[] = {
        -1,  2,
        -3, -4
    };

    Matrix *a = mat_from_array(2, 2, values);
    Matrix *c = matc_allocate(2, 2);

    CHECK(a != NULL);
    CHECK(c != NULL);

    matc_scale(c, a, 3);
    CHECK(mat_equals(c, 2, 2, expected_positive));

    matc_scale(c, a, 0);
    CHECK(mat_equals(c, 2, 2, expected_zero));

    matc_scale(c, a, -1);
    CHECK(mat_equals(c, 2, 2, expected_negative));

    matc_free(a);
    matc_free(c);
    return 1;
}

static int test_transpose_rectangular(void) {
    /* (2 x 3) -> (3 x 2) */
    const int values[] = {
        1, 2, 3,
        4, 5, 6
    };
    const int expected[] = {
        1, 4,
        2, 5,
        3, 6
    };

    Matrix *a = mat_from_array(2, 3, values);
    Matrix *c = matc_allocate(3, 2);

    CHECK(a != NULL);
    CHECK(c != NULL);

    matc_transpose(c, a);
    CHECK(mat_equals(c, 3, 2, expected));

    matc_free(a);
    matc_free(c);
    return 1;
}

static int test_transpose_square(void) {
    const int values[] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    const int expected[] = {
        1, 4, 7,
        2, 5, 8,
        3, 6, 9
    };

    Matrix *a = mat_from_array(3, 3, values);
    Matrix *c = matc_allocate(3, 3);

    CHECK(a != NULL);
    CHECK(c != NULL);

    matc_transpose(c, a);
    CHECK(mat_equals(c, 3, 3, expected));

    matc_free(a);
    matc_free(c);
    return 1;
}

static int test_alias_safe_elementwise_operations(void) {
    /* sum/sub/scale do not require a separate output matrix */
    const int initial[] = {
        1, 2,
        3, 4
    };
    const int sum_expected[] = {
        2, 4,
        6, 8
    };
    const int sub_expected[] = {
        1, 2,
        3, 4
    };
    const int scale_expected[] = {
        3, 6,
        9, 12
    };

    Matrix *a = mat_from_array(2, 2, initial);
    Matrix *b = mat_from_array(2, 2, initial);

    CHECK(a != NULL);
    CHECK(b != NULL);

    matc_sum(a, a, b);
    CHECK(mat_equals(a, 2, 2, sum_expected));

    matc_sub(a, a, b);
    CHECK(mat_equals(a, 2, 2, sub_expected));

    matc_scale(a, a, 3);
    CHECK(mat_equals(a, 2, 2, scale_expected));

    matc_free(a);
    matc_free(b);
    return 1;
}

int main(void) {
    int failures = 0;

    printf("Running MatC test suite...\n\n");

#define RUN_TEST(test)                                                          \
    do {                                                                        \
        printf("%-42s", #test);                                                 \
        if (test()) {                                                           \
            printf("PASS\n");                                                  \
        } else {                                                                \
            printf("FAIL\n");                                                  \
            ++failures;                                                         \
        }                                                                       \
    } while (0)

    RUN_TEST(test_allocate_and_access);
    RUN_TEST(test_fill);
    RUN_TEST(test_sum);
    RUN_TEST(test_sub);
    RUN_TEST(test_mul_square);
    RUN_TEST(test_mul_rectangular);
    RUN_TEST(test_mul_with_ones_and_zeros);
    RUN_TEST(test_scale);
    RUN_TEST(test_transpose_rectangular);
    RUN_TEST(test_transpose_square);
    RUN_TEST(test_alias_safe_elementwise_operations);

#undef RUN_TEST

    printf("\nChecks: %d passed / %d run\n", tests_passed, tests_run);

    if (failures != 0) {
        printf("Test suite FAILED\n");
        return EXIT_FAILURE;
    }

    printf("Test suite PASSED\n");
    return EXIT_SUCCESS;
}
