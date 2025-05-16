#include "mtx_oper.h"

int matrix_add (matrix *m1, const matrix *m2)
{
    if (!m1 || !m2 || matrix_h(m1) != matrix_h(m2) ||
    matrix_w(m1) != matrix_w(m2)) return -1;

    for (size_t i = 0; i < matrix_h(m1); ++i)
    {
        for (size_t j = 0; j < matrix_w(m1); ++j)
        {
            *matrix_ptr(m1, i, j) += *matrix_cptr(m2, i, j);
        }
    }
    return 0;
}

int matrix_sub (matrix *m1, const matrix *m2)
{
    if (!m1 || !m2 || matrix_h(m1) != matrix_h(m2) ||
    matrix_w(m1) != matrix_w(m2)) return -1;

    for (size_t i = 0; i < matrix_h(m1); ++i)
    {
        for (size_t j = 0; j < matrix_w(m1); ++j)
        {
            *matrix_ptr(m1, i, j) -= *matrix_cptr(m2, i, j);
        }
    }
    return 0;
}

void matrix_smul (matrix *m, double d)
{
    if (!m) return;

    for (size_t i = 0; i < matrix_h(m); ++i)
    {
        for (size_t j = 0; j < matrix_w(m); ++j)
        {
            *matrix_ptr(m, i, j) *= d;
        }
    }
}
void matrix_sdiv (matrix *m, double d)
{
    if (!m || d == 0.0) return;

    matrix_smul (m, 1 / d);
}

int matrix_add2 (matrix *m, const matrix *m1, const matrix *m2)
{
    if (!m || !m1 || !m2 ||
        matrix_w(m) != matrix_w(m1) || matrix_h(m) != matrix_h(m1) ||
        matrix_w(m) != matrix_w(m2) || matrix_h(m) != matrix_h(m2)) return -1;

    matrix_assign(m, m1);
    matrix_add(m, m2);
}

int matrix_sub2 (matrix *m, const matrix *m1, const matrix *m2)
{
    if (!m || !m1 || !m2 ||
        matrix_w(m) != matrix_w(m1) || matrix_h(m) != matrix_h(m1) ||
        matrix_w(m) != matrix_w(m2) || matrix_h(m) != matrix_h(m2)) return -1;

    matrix_assign(m, m1);
    matrix_sub(m, m2);
}

int matrix_smul2 (matrix *m, const matrix *m1, double d)
{
    if (!m || !m1 ||
        matrix_w(m) != matrix_w(m1) || matrix_h(m) != matrix_h(m1)) return -1;

    matrix_assign(m, m1);
    matrix_smul(m, d);
}

int matrix_sdiv2 (matrix *m, const matrix *m1, double d)
{
    if (!m || !m1 ||
        matrix_w(m) != matrix_w(m1) || matrix_h(m) != matrix_h(m1)) return -1;

    matrix_assign(m, m1);
    matrix_sdiv(m, d);
}

int matrix_mul(matrix *m1, const matrix *m2)
{
    if (!m1 || !m2 || matrix_w(m1) != matrix_h(m2)) 
        return -1;
    
    const size_t h = matrix_h(m1);
    const size_t w = matrix_w(m2);
    const size_t inner = matrix_w(m1);

    matrix *result = matrix_alloc(h, w);
    if (!result) return -1;
    
    for (size_t i = 0; i < h; ++i)
    {
        for (size_t j = 0; j < w; ++j)
        {
            double sum = 0.0;
            for (size_t k = 0; k < inner; ++k)
            {
                sum += matrix_get(m1, i, k) * matrix_get(m2, k, j);
            }
            matrix_set(result, i, j, sum);
        }
    }

    if (matrix_realloc(m1, h, w) == -1)
    {
        matrix_free(result);
        return -1;
    }
    
    if (matrix_assign(m1, result) == -1)
    {
        matrix_free(result);
        return -1;
    }
    
    matrix_free(result);
    return 0;
}

int matrix_mul2 (matrix *m, const matrix *m1, const matrix *m2)
{
    if (!m || !m1 || !m2) return -1;
    if (matrix_realloc(m, matrix_h(m1), matrix_w(m1)) == -1 || matrix_assign(m, m1) == -1) return -1;

    matrix_mul(m, m2);

    return 0;
}