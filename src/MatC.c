#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "MatC.h"

Matrix *matc_allocate(size_t rows, size_t columns) {
    if (rows <= 0 || columns <= 0) return NULL; // Cannot allocate 0 or negative cells

    Matrix *matrix = malloc(sizeof(Matrix));
    if (matrix == NULL) return NULL;

    matrix->data = malloc(sizeof(int) * (rows * columns));
    if (matrix->data == NULL) {
        free(matrix);
        return NULL;
    }

    matrix->rows = rows;
    matrix->columns = columns;

    return matrix;
}

void matc_free(Matrix *matrix) {
    free(matrix->data);
    free(matrix);
}

int *matc_at(const Matrix *matrix, size_t i, size_t j) {
    return &matrix->data[i * matrix->columns + j]; // i = rows, j = columns
}

void matc_fill(Matrix *matrix, int value) {
    for (size_t i = 0; i < matrix->rows; ++i) {
        for (size_t j = 0; j < matrix->columns; ++j) {
            *matc_at(matrix, i, j) = value;
        }
    }
}

void matc_print(const Matrix *matrix) {
    for (size_t i = 0; i < matrix->rows; ++i) {
        printf("[ ");
        for (size_t j = 0; j < matrix->columns; ++j) {
            printf("%d ", *matc_at(matrix, i, j));
        }
        printf("]\n");
    }
}

void matc_sum(Matrix *c, const Matrix *a, const Matrix *b) {
    // All matrices should be of the same dimensions.
    assert(a->rows == b->rows && b->rows == c->rows);
    assert(a->columns == b->columns && b->columns == c->columns);

    for (size_t i = 0; i < a->rows; ++i) {
        for (size_t j = 0; j < a->columns; ++j) {
            *matc_at(c, i, j) = *matc_at(a, i, j) + *matc_at(b, i, j);
        }
    }
}

void matc_sub(Matrix *c, const Matrix *a, const Matrix *b) {
    assert(a->rows == b->rows && b->rows == c->rows);
    assert(a->columns == b->columns && b->columns == c->columns);

    for (size_t i = 0; i < a->rows; ++i) {
        for (size_t j = 0; j < a->columns; ++j) {
            *matc_at(c, i, j) = *matc_at(a, i, j) - *matc_at(b, i, j);
        }
    }
}

void matc_mul(Matrix *c, const Matrix *a, const Matrix *b) {
    // a should be of size m * n, b should be of size n * p and c should be of size m * p
    assert(a->columns == b->rows);
    assert(c->rows == a->rows && c->columns == b->columns);

    for (size_t i = 0; i < a->rows; ++i) {
        for(size_t j = 0; j < b->columns; ++j) {
            *matc_at(c, i, j) = 0;
            for (size_t k = 0; k < a->columns; ++k) {
                *matc_at(c, i, j) += *matc_at(a, i, k) * *matc_at(b, k, j);
            }
        }
    }
}

void matc_scale(Matrix *c, const Matrix *a, const int scale) {
    for (size_t i = 0; i < a->rows; ++i) {
        for (size_t j = 0; j < a->columns; ++j) {
            *matc_at(c, i, j) = *matc_at(a, i, j) * scale;
        }
    }
}

void matc_transpose(Matrix *c, const Matrix *a) {
    assert(a->rows == c->columns);
    assert(a->columns == c->rows);

    for (size_t i = 0; i < a->rows; ++i) {
        for (size_t j = 0; j < a->columns; ++j) {
            *matc_at(c, j, i) = *matc_at(a, i, j);
        }
    }
}
