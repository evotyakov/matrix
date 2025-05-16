#pragma once

#include "mtx_adt.h"
#include "mtx_oper.h"
#include "mtx_man.h"

// Матричная экспонента, A - квадратная матрица
matrix * matrix_exp(const matrix *A, double eps);

// Решение СЛАУ: метод Гаусса
matrix * matrix_gauss_method (matrix *A, matrix *B);

// Проверка решения
int verify_solution(const matrix* A, const matrix* X, const matrix* B, double eps);