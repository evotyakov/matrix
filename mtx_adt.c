#include "mtx_adt.h"

struct matrix
{
    double *data;
    size_t h, w;
};

matrix * matrix_alloc (size_t h, size_t w)
{
    matrix *m = malloc(sizeof(matrix));
    if (!m) return NULL;
    m->w = w;
    m->h = h;
    m->data = malloc(w * h * sizeof(double));
    if (!m->data)
    {
        free(m);
        return NULL;
    }
    return m;
}

int matrix_realloc (matrix *m, size_t h, size_t w)
{
    if (!m) return -1;
    free(m->data);
    m->w = w;
    m->h = h;
    m->data = malloc(w * h * sizeof(double));
    if (!m->data)
    {
        free(m);
        return -1;
    }
    return 0;
}

matrix * matrix_copy (const matrix *m)
{
    if (!m || !m->data) return NULL;

    matrix *m_new = malloc(sizeof(matrix));
    if (!m_new) return NULL;

    m_new->w = m->w;
    m_new->h = m->h;

    m_new->data = malloc(m->w * m->h * sizeof(double));
    if (!m_new->data)
    {
        free(m_new);
        return NULL;
    }
    memcpy(m_new->data, m->data, m->w * m->h * sizeof(double));

    return m_new;
}

void matrix_free (matrix *m)
{
    if (!m) return;

    if (m->data != NULL)
    {
        free(m->data);
        m->data = NULL;
    }

    free(m);
}

double * matrix_ptr (matrix *m, size_t i, size_t j)
{
    return &m->data[i * m->w + j];
}

const double * matrix_cptr (const matrix *m, size_t i, size_t j)
{
    return &m->data[i * m->w + j];
}

void matrix_set(matrix *m, int i, int j, double val)
{
    if (!m || !m->data || i < 0 || j < 0 ||
        i >= (int)m->h || j >= (int)m->w)
        return;

    m->data[i * m->w + j] = val;
}

double matrix_get(const matrix *m, int i, int j)
{
    if (!m || !m->data || i < 0 || j < 0 ||
        i >= (int)m->h || j >= (int)m->w)
        return NAN;

    return m->data[i * m->w + j];
}

void matrix_set_zero (matrix *m)
{
    if (!m || !m->data) return;

    memset(m->data, 0, m->h * m->w * sizeof(double));
}

void matrix_set_id (matrix *m)
{
    if (!m || !m->data) return;

    for (size_t i = 0; i < m->h; ++i)
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            *matrix_ptr(m, i, j) = (i == j) ? 1.0 : 0.0;
        }
    }
}

matrix * matrix_alloc_zero (size_t h, size_t w)
{
    matrix *m = matrix_alloc(h, w);
    if (!m) return NULL;

    memset(m->data, 0, w * h * sizeof(double));
    return m;
}

matrix * matrix_alloc_id (size_t h, size_t w)
{
    matrix *m = matrix_alloc(h, w);
    if (!m) return NULL;

    for (size_t i = 0; i < m->h; ++i)
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            *matrix_ptr(m, i, j) = (i == j) ? 1.0 : 0.0;
        }
    }
    return m;
}

int matrix_assign (matrix *m1, const matrix *m2)
{
    if (!m1 || !m2 || m1->h != m2->h || m1->w != m2->w)
        return -1;
    
    memcpy(m1->data, m2->data, m1->w * m1->h * sizeof(double));
    return 0;
}

void matrix_input (matrix *m)
{
    if (!m || !m->data) return;

    printf("Enter the matrix %zux%zu:\n\n", m->h, m->w);
    
    for (size_t i = 0; i < m->h; ++i)
    {       
        for (size_t j = 0; j < m->w; ++j)
        {
            while (scanf("%lf", matrix_ptr(m, i, j)) != 1)
            {
                fprintf(stderr, "Error");
                while (getchar() != '\n');
            }
        }
    }
    printf("\n");
}

void matrix_output (matrix *m)
{
    if (!m || !m->data) return;

    for (size_t i = 0; i < m->h; ++i)
    {
        for (size_t j = 0; j < m->w; ++j)
        {
            printf("%5.2f ", *matrix_cptr(m, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

size_t matrix_w (const matrix *m)
{
    return m ? m->w : 0;
}

size_t matrix_h (const matrix *m)
{
    return m ? m->h : 0;
}