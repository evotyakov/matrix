#include "mtx_man.h"

int matrix_transpose(matrix *m)
{
    if (!m) return -1;

    if (matrix_h(m) == matrix_w(m))
    {
        for (size_t i = 0; i < matrix_h(m); ++i)
        {
            for (size_t j = i + 1; j < matrix_w(m); ++j)
            {
                double tmp = *matrix_ptr(m, i, j);
                *matrix_ptr(m, i, j) = *matrix_ptr(m, j, i);
                *matrix_ptr(m, j, i) = tmp;
            }
        }
        return 0;
    }

    matrix *m_new = matrix_alloc(matrix_w(m), matrix_h(m));
    if (!m_new) return -1;

    for (size_t i = 0; i < matrix_h(m); ++i)
    {
        for (size_t j = 0; j < matrix_w(m); ++j)
        {
            *matrix_ptr(m_new, j, i) = *matrix_ptr(m, i, j);
        }
    }

    if (matrix_realloc(m, matrix_w(m), matrix_h(m)) == -1)
    {
        matrix_free(m_new);
        return -1;
    }
    
    if (matrix_assign(m, m_new) == -1)
    {
        matrix_free(m_new);
        return -1;
    }

    matrix_free(m_new);
    return 0;
}

int matrix_swap_rows (matrix *m, size_t row1, size_t row2)
{
    if (!m || row1 < 1 || row2 < 1 ||
        row1 > matrix_h(m) || row2 > matrix_h(m)) return -1;
    --row1; --row2;

    for (size_t j = 0; j < matrix_w(m); ++j)
    {
        double el = *matrix_ptr(m, row1, j);
        *matrix_ptr(m, row1, j) = *matrix_ptr(m, row2, j);
        *matrix_ptr(m, row2, j) = el;
    }
    return 0;
}

int matrix_swap_cols (matrix *m, size_t col1, size_t col2)
{
    if (!m || col1 < 1 || col2 < 1 ||
        col1 > matrix_w(m) || col2 > matrix_w(m)) return -1;
    --col1; --col2;

    for (size_t i = 0; i < matrix_h(m); ++i)
    {
        double el = *matrix_ptr(m, i, col1);
        *matrix_ptr(m, i, col1) = *matrix_ptr(m, i, col2);
        *matrix_ptr(m, i, col2) = el;
    }
    return 0;
}

int matrix_row_smul (matrix *m, size_t row, double d)
{
    if (!m || row < 1 || row > matrix_h(m)) return -1;
    --row;

    for (size_t j = 0; j < matrix_w(m); ++j)
    {
        *matrix_ptr(m, row, j) *= d;
    }
    return 0;
}

int matrix_row_sdiv (matrix *m, size_t row, double d)
{
    if (d == 0.0) return -1;
    return matrix_row_smul(m, row, 1.0 / d);
}

int matrix_rows_add (matrix *m, size_t row1, size_t row2)
{
    --row1; --row2;
    if (!m || row1 < 0 || row2 < 0 ||
        row1 >= matrix_h(m) || row2 >= matrix_h(m)) return -1;

    for (size_t j = 0; j < matrix_w(m); ++j)
    {
        *matrix_ptr(m, row1, j) += *matrix_cptr(m, row2, j);
    }
    return 0;
}

double matrix_norm (const matrix *m)
{
    if (!m) return NAN;

    double max = 0.0;
    for (size_t i = 0; i < matrix_h(m); ++i)
    {
        double sum = 0.0;
        for (size_t j = 0; j < matrix_w(m); ++j)
        {
            sum += fabs(*matrix_cptr(m, i, j));
        }
        if (sum > max) max = sum;
    }
    return max;
}