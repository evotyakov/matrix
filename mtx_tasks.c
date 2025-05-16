#include "mtx_tasks.h"

matrix * matrix_exp(const matrix *A, double eps)
{
    if (!A || matrix_h(A) != matrix_w(A)) return NULL;

    const size_t n = matrix_h(A);
    matrix* expA = matrix_alloc_id(n, n);
    matrix* term = matrix_alloc_id(n, n);
    matrix* temp = NULL;

    if (!expA || !term)
    {
        matrix_free(expA);
        matrix_free(term);
        return NULL;
    }

    int k = 1;
    double norm;

    do
    {
        temp = matrix_alloc(n, n);
        if (!temp || matrix_mul2(temp, term, A) != 0)
        {
            matrix_free(temp);
            matrix_free(expA);
            matrix_free(term);
            return NULL;
        }
        matrix_free(term);
        term = temp;

        matrix_sdiv(term, k);

        if (matrix_add(expA, term) != 0)
        {
            matrix_free(expA);
            matrix_free(term);
            return NULL;
        }

        norm = matrix_norm(term);
        k++;
    }
    while (norm >= eps);

    matrix_free(term);
    return expA;
}

matrix * matrix_gauss_method (matrix *A, matrix *B)
{
    if (!A || !B || matrix_h(A) != matrix_w(A) ||
    matrix_h(A) != matrix_h(B)) return NULL;

    const size_t n = matrix_h(A);
    matrix* X = matrix_alloc(n, 1);
    matrix* tempA = matrix_copy(A);

    if (!X || !tempA)
    {
        matrix_free(X);
        matrix_free(tempA);
        return NULL;
    }

    for (size_t i = 0; i < n; ++i)
    {
        *matrix_ptr(X, i, 0) = *matrix_ptr(B, i, 0);
    }

    for (size_t i = 0; i < n; ++i)
    {
        size_t max_row = i;
        double max_val = fabs(*matrix_ptr(tempA, i, i));

        for (size_t k = i + 1; k < n; ++k)
        {
            double val = fabs(*matrix_ptr(tempA, k, i));
            if (val > max_val)
            {
                max_val = val;
                max_row = k;
            }
        }

        if (max_row != i)
        {
            matrix_swap_rows(tempA, i, max_row);
            matrix_swap_rows(X, i, max_row);
        }

        if (fabs(*matrix_ptr(tempA, i, i)) < 1e-12)
        {
            matrix_free(tempA);
            matrix_free(X);
            return NULL;
        }

        double diag = *matrix_ptr(tempA, i, i);
        for (size_t j = i; j < n; ++j)
        {
            *matrix_ptr(tempA, i, j) /= diag;
        }
        *matrix_ptr(X, i, 0) /= diag;

        for (size_t k = i + 1; k < n; ++k)
        {
            double factor = *matrix_ptr(tempA, k, i);
            for (size_t j = i; j < n; ++j)
            {
                *matrix_ptr(tempA, k, j) -= factor * *matrix_ptr(tempA, i, j);
            }
            *matrix_ptr(X, k, 0) -= factor * *matrix_ptr(X, i, 0);
        }
    }

    for (int i = n - 1; i >= 0; --i)
    {
        for (int k = i - 1; k >= 0; --k)
        {
            double factor = *matrix_ptr(tempA, k, i);
            *matrix_ptr(tempA, k, i) = 0.0;
            *matrix_ptr(X, k, 0) -= factor * *matrix_ptr(X, i, 0);
        }
    }

    matrix_free(tempA);
    return X;
}

int verify_solution(const matrix* A, const matrix* X, const matrix* B, double eps)
{
    if (!A || !X || !B || 
        matrix_h(A) != matrix_w(A) || 
        matrix_w(A) != matrix_h(X) || 
        matrix_h(X) != matrix_h(B) || 
        matrix_w(B) != 1) return -1;

    matrix* AX = matrix_alloc(matrix_h(A), matrix_w(X));
    if (!AX || matrix_mul2(AX, A, X) != 0)
    {
        matrix_free(AX);
        return -1;
    }

    matrix *residual = matrix_alloc(matrix_h(B), matrix_w(B));
    if (!residual || matrix_sub2(residual, AX, B) != 0)
    {
        matrix_free(AX);
        matrix_free(residual);
        return -1;
    }

    double norm = matrix_norm(residual);

    matrix_free(AX);
    matrix_free(residual);

    return (norm < eps) ? 0 : 1;
}