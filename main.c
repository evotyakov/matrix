#include <stdio.h>
#include <stdlib.h>

#include "mtx_adt.h"
#include "mtx_man.h"
#include "mtx_oper.h"
#include "mtx_tasks.h"

void print_table()
{
    printf("Enter the test:\n\n"
        "1. Abstract Data Type\n"
        "2. Operations\n"
        "3. Manipulations\n"
        "4. The matrix exponent\n"
        "5. The Gauss method\n\n");
}

int main()
{
    size_t choice;
    print_table();
    scanf("%zu", &choice);
    printf("\n");

    switch (choice)
    {
        case 1:
        {
            matrix *m = matrix_alloc(3, 3);
            matrix_set_id(m);
            matrix_output(m);
            matrix_free(m);

            m = matrix_alloc_zero(2, 3);
            matrix_set(m, 0, 2, 3.0);
            matrix_output(m);
            matrix_free(m);

            m = matrix_alloc_id(3, 3);
            matrix *m2 = matrix_copy(m);
            matrix_output(m2);
            matrix_free(m);
            matrix_free(m2);

            m = matrix_alloc(3, 2);
            matrix_input(m);
            printf("(2, 2) = %.2f\n\n", matrix_get(m, 1, 1));
            matrix_output(m);
            matrix_free(m);

            break;
        }

        case 2:
        {
            // 1
            matrix *m = matrix_alloc(2, 3);
            matrix_input(m);
            matrix *m1 = matrix_alloc_id(2, 3);

            matrix_add(m, m1);
            matrix_output(m);

            matrix_sub(m, m1);
            matrix_output(m);

            matrix_smul(m, 2.0);
            matrix_output(m);

            matrix_sdiv(m, 2.0);
            matrix_output(m);
            
            // 2
            matrix *m2 = matrix_alloc(2, 3);
            matrix_input(m2);

            matrix_add2(m, m1, m2);
            matrix_output(m);

            matrix_sub2(m, m1, m2);
            matrix_output(m);

            matrix_smul2(m, m2, 2.0);
            matrix_output(m);

            matrix_sdiv2(m, m2, 2.0);
            matrix_output(m);

            // 3            
            matrix *m3 = matrix_alloc(3, 2);
            matrix_input(m3);

            matrix_mul(m, m3);
            matrix_output(m);

            matrix_mul2(m1, m, m3);
            matrix_output(m1);

            matrix_free(m);
            matrix_free(m1);
            matrix_free(m2);
            matrix_free(m3);

            break;
        }

        case 3:
        {
            matrix *m = matrix_alloc(3, 3);
            matrix_input(m);

            matrix_transpose(m);
            matrix_output(m);

            matrix_swap_rows(m, 1, 3);
            matrix_output(m);

            matrix_swap_cols(m, 1, 3);
            matrix_output(m);

            matrix_row_smul(m, 2, 2.0);
            matrix_output(m);

            matrix_row_sdiv(m, 2, 2.0);
            matrix_output(m);

            matrix_rows_add(m, 1, 3);
            matrix_output(m);

            printf("Matrix norm = %.2lf", matrix_norm(m));
            matrix_free(m);

            break;
        }

        case 4:
        {
            matrix *m = matrix_alloc(3, 3);
            matrix_input(m);
            matrix *res = matrix_exp(m, 1e-6);
            matrix_output(res);

            matrix_free(m);
            matrix_free(res);

            break;
        }

        case 5:
        {
            matrix *A = matrix_alloc(2, 2);
            matrix_input(A);
            matrix *B = matrix_alloc(2, 1);
            matrix_input(B);
            matrix *X = matrix_gauss_method(A, B);
            if (!verify_solution(A, X, B, 1e-6)) matrix_output(X);

            matrix_free(A);
            matrix_free(B);
            matrix_free(X);

            break;
        }
        
        default:
            break;    
    }

    return 0;
}