#pragma once

#include "mtx_adt.h"

// m1 += m2, m1 -= m2, m *= d, m /= d
// 0 - успех, -1 - ошибка (разные размеры)
int matrix_add (matrix *m1, const matrix *m2);
int matrix_sub (matrix *m1, const matrix *m2);
void matrix_smul (matrix *m, double d);
void matrix_sdiv (matrix *m, double d);

// m = m1 + m2, m = m1 - m2, m = m1 * d, m = m1 / d
// 0 - успех, -1 - ошибка (разные размеры)
int matrix_add2 (matrix *m, const matrix *m1, const matrix *m2);
int matrix_sub2 (matrix *m, const matrix *m1, const matrix *m2);
int matrix_smul2 (matrix *m, const matrix *m1, double d);
int matrix_sdiv2 (matrix *m, const matrix *m1, double d);

int matrix_mul (matrix *m1, const matrix *m2);  // Только для квадратных матриц

// m = m1 * m2
/* Возможно, нужна доп матрица, если m == m1 || m == m2
    alloc->assign->free
    например matrix_mul (a, a, b) - через доп. матрицу
    например matrix_mul (с, a, b) - без доп. матрицы
*/
int matrix_mul2 (matrix *m, const matrix *m1, const matrix *m2);
