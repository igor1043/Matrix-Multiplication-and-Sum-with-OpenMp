#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "matriz2d.h"

int main( int argc, char** argv )
{
    int lin1, col1, lin2, col2;
	double time1, time2;
	
	time1 = omp_get_wtime();
	int **matriz_1 = matriz2d_alloc( "matriz_op_multi1.dat", &lin1, &col1 );
	int **matriz_2 = matriz2d_alloc( "matriz_op_multi2.dat", &lin2, &col2 );
	int **matriz_3 = matriz2d_alloc_vazio( lin1, col1 );
	time2 = omp_get_wtime();
	printf("Tempo gasto para ler do disco e alocar memória: %f\n", time2 - time1 );
	printf("Matriz1 linhas: %d, colunas: %d, Matriz2 linhas: %d, colunas: %d\n", lin1, col1, lin2, col2 );

	//matriz2d_print( matriz_1, 4, 3 );
	printf( "\n" );
	//matriz2d_print( matriz_2, lin2, col2 );

	//Multiplicando Matrizes.
	time1 = omp_get_wtime();
	matriz2d_multiplica( matriz_1, matriz_2, matriz_3, lin1, col1, lin2, col2 );
	time2 = omp_get_wtime();	
	printf("Tempo gasto na operação de multiplicação: %f\n", time2 - time1 );
	
	time1 = omp_get_wtime();
	matriz2d_save_to_file( "matriz_resultado_multi.dat", matriz_3, lin1, col1 );
	time2 = omp_get_wtime();
	printf("Tempo gasto salvar no disco: %f\n", time2 - time1 );

	time1 = omp_get_wtime();
	matriz2d_free( matriz_1, lin1 );
	matriz2d_free( matriz_2, lin2 );
	matriz2d_free( matriz_3, lin2 );
	time2 = omp_get_wtime();
	printf("Tempo gasto para desalocar memória: %f\n", time2 - time1 );

    return (EXIT_SUCCESS );
}
