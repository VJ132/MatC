#include <stdio.h>

#include "src/MatC.h"

static void section(const char *title) {
    printf("\n=== %s ===\n", title);
}

static void safe_free(Matrix **matrix) {
    if (matrix != NULL && *matrix != NULL) {
        matc_free(*matrix);
        *matrix = NULL;
    }
}

int main(void) {
    Matrix *a = NULL;
    Matrix *b = NULL;
    Matrix *sum = NULL;
    Matrix *sub = NULL;
    Matrix *scaled = NULL;
    Matrix *b2 = NULL;
    Matrix *product = NULL;
    Matrix *transpose = NULL;

    /* ----------------------------------------------------------
     * Matrix creation and filling
     * ---------------------------------------------------------- */
    section("Create and fill");

    a = matc_allocate(2, 3);
    if (a == NULL)
        return 1;

    matc_fill(a, 2);
    printf("A (2x3):\n");
    matc_print(a);

    /* Direct element access. */
    *matc_at(a, 0, 1) = 10;

    printf("A after changing A[0][1] to 10:\n");
    matc_print(a);

    /* ----------------------------------------------------------
     * Matrix addition and subtraction
     * ---------------------------------------------------------- */
    section("Addition and subtraction");

    b = matc_allocate(2, 3);
    sum = matc_allocate(2, 3);
    sub = matc_allocate(2, 3);

    if (b == NULL || sum == NULL || sub == NULL)
        goto cleanup;

    matc_fill(b, 3);

    printf("B (2x3):\n");
    matc_print(b);

    matc_sum(sum, a, b);
    printf("A + B:\n");
    matc_print(sum);

    matc_sub(sub, a, b);
    printf("A - B:\n");
    matc_print(sub);

    /* ----------------------------------------------------------
     * Scalar multiplication
     * ---------------------------------------------------------- */
    section("Scalar multiplication");

    scaled = matc_allocate(2, 3);
    if (scaled == NULL)
        goto cleanup;

    matc_scale(scaled, a, 2);
    printf("2A:\n");
    matc_print(scaled);

    /* ----------------------------------------------------------
     * Matrix multiplication
     * ---------------------------------------------------------- */
    section("Matrix multiplication");

    /* A is 2x3, so B2 must be 3x2. */
    b2 = matc_allocate(3, 2);
    product = matc_allocate(2, 2);

    if (b2 == NULL || product == NULL)
        goto cleanup;

    /*
     * B2 = [ 1 2 ]
     *       [ 3 4 ]
     *       [ 5 6 ]
     */
    *matc_at(b2, 0, 0) = 1;
    *matc_at(b2, 0, 1) = 2;
    *matc_at(b2, 1, 0) = 3;
    *matc_at(b2, 1, 1) = 4;
    *matc_at(b2, 2, 0) = 5;
    *matc_at(b2, 2, 1) = 6;

    printf("B2 (3x2):\n");
    matc_print(b2);

    matc_mul(product, a, b2);
    printf("A * B2:\n");
    matc_print(product);

    /* ----------------------------------------------------------
     * Transpose
     * ---------------------------------------------------------- */
    section("Transpose");

    transpose = matc_allocate(a->columns, a->rows);
    if (transpose == NULL)
        goto cleanup;

    matc_transpose(transpose, a);
    printf("A^T:\n");
    matc_print(transpose);

cleanup:
    /* ----------------------------------------------------------
     * Cleanup
     * ---------------------------------------------------------- */
    safe_free(&a);
    safe_free(&b);
    safe_free(&sum);
    safe_free(&sub);
    safe_free(&scaled);
    safe_free(&b2);
    safe_free(&product);
    safe_free(&transpose);

    return 0;
}
