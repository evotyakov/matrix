#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

typedef struct matrix matrix;

matrix * matrix_alloc (size_t h, size_t w);
int matrix_realloc (matrix *m, size_t h, size_t w);
matrix * matrix_copy (const matrix *m);

void matrix_free (matrix *m);

double * matrix_ptr (matrix *m, size_t i, size_t j);
const double * matrix_cptr (const matrix *m, size_t i, size_t j);

void matrix_set(matrix *m, int i, int j, double val);
double matrix_get(const matrix *m, int i, int j);

void matrix_set_zero (matrix *m);
void matrix_set_id (matrix *m);

matrix * matrix_alloc_zero (size_t h, size_t w);
matrix * matrix_alloc_id (size_t h, size_t w);

int matrix_assign (matrix *m1, const matrix *m2);

void matrix_input (matrix *m);
void matrix_output (matrix *m);

size_t matrix_w (const matrix *m);
size_t matrix_h (const matrix *m);
