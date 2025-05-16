#pragma once

#include "mtx_adt.h"

// Транспонирование (на месте)
int matrix_transpose (matrix *m);

// Перестановка строк (на месте)
int matrix_swap_rows (matrix *m, size_t row1, size_t row2);

// Перестановка столбцов (на месте)
int matrix_swap_cols (matrix *m, size_t col1, size_t col2);

// Умножение/деление строки на число
int matrix_row_smul (matrix *m, size_t row, double d);
int matrix_row_sdiv (matrix *m, size_t row, double d);

// Сложение двух строк
int matrix_rows_add (matrix *m, size_t row1, size_t row2);

// Норма матрицы
double matrix_norm (const matrix *m);