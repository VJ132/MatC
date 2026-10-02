#ifndef MATC_H
#define MATC_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t rows;
    size_t columns;
} Matrix;

Matrix *matc_allocate(size_t rows, size_t columns);
void matc_free(Matrix *matrix);

void matc_fill(Matrix *matrix, int value);

int *matc_at(const Matrix *matrix, size_t i, size_t j);

void matc_print(const Matrix *matrix);

void matc_sum(Matrix *c, const Matrix *a, const Matrix *b); // C = A + B
void matc_sub(Matrix *c, const Matrix *a, const Matrix *b); // C = A - B
void matc_mul(Matrix *c, const Matrix *a, const Matrix *b); // C = AB
void matc_scale(Matrix *c, const Matrix *a, const int scalar); // C = A * scalar

void matc_transpose(Matrix *c, const Matrix *a);

#endif // MATC_H
