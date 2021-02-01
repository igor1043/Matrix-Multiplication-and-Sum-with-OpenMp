#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>

#define NUM_THREADS 4 //Quantidade de threads

int **matriz_1, **matriz_2, **matriz_3;

typedef struct{
	int inicio;
	int fim;
	int qtdLinhas;
	int linhas1, linhas2;
	int colunas1, colunas2;
} thread_arg;

void matriz2d_print(int **matriz, int lin, int col)
{
    int i, j;

    for (i = 0; i < lin; i++)
    {
        if (col >= 1)
            printf("| %d", matriz[i][0]);
        for (j = 1; j < col; j++)
        {
            printf(", %d", matriz[i][j]);
        }
        printf(" |\n");
    }
}

int** matriz2d_alloc(char *nome_arquivo, int *lin, int *col)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    int **matriz = NULL;
    int i, j;

    if (arquivo != NULL)
    {

        fscanf(arquivo, "%d %d\n", lin, col);

        //alocando memória para matriz.
        matriz = malloc(*lin * sizeof (int*));
        for (i = 0; i < *lin; i++)
        {
            matriz[i] = malloc(*col * sizeof (int));
        }

        //carrega a matriz na memória.
        for (i = 0; i < *lin; i++)
        {
            for (j = 0; j < *col; j++)
            {
                fscanf(arquivo, "%d", &matriz[i][j]);
            }
        }
        fclose(arquivo);
    }
    return matriz;
}

int** matriz2d_alloc_vazio(int lin, int col)
{
    int **matriz = NULL;
    int i, j;

    //alocando memória para matriz.
    matriz = (int**) calloc(lin, sizeof(int*));
    for (i = 0; i < lin; i++)
    {
        matriz[i] = (int*) calloc(col, sizeof(int));
    }

    return matriz;
}

int** matriz2d_alloc_rand(int lin, int col)
{
    int **matriz = NULL;
    int i, j;

    //alocando memória para matriz.
    matriz = (int**) calloc(lin, sizeof(int*));
	
	//setando a semente do rand();
	srand(time(0));
	
    for (i = 0; i < lin; i++)
    {
        matriz[i] = (int*) calloc(col, sizeof(int));
		for (j = 0; j < col; j++) {
			matriz[i][j] = rand() % 100;
		}
    }

    return matriz;
}

int matriz2d_save_to_file(char *nome_arquivo, int **matriz, int lin, int col)
{
    FILE *arquivo = fopen(nome_arquivo, "w+");
    int i, j;

    if (arquivo != NULL)
    {
        fprintf(arquivo, "%d %d\n", lin, col);
        for ( i = 0; i < lin; i++ )
        {
            for ( j = 0; j < col; j++ )
            fprintf(arquivo, "%d\n", matriz[i][j]);
        }
        fclose(arquivo);
        return 1;
    }
    
    return 0;
}

void matriz2d_free(int ** matriz, int lin)
{
    int i;

    if(matriz == NULL){
        return NULL;
    }

    for (i = 0; i < lin; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

void *matriz2d_multiplica(void *arg)
{
    int i, j, k;
    thread_arg *a = (thread_arg*) arg;
    if ( a->colunas1 != a->linhas2 ) {
        fprintf(stderr, "Não é possível multiplicar as matrizes\n");
        exit(EXIT_FAILURE);
    }

    for (i = a->inicio; i < a->fim; i++){
        for (j = 0; j < a->colunas2; j++){
            for (k = 0; k < a->colunas1; k++){
                matriz_3[i][j] += matriz_1[i][k] * matriz_2[k][j];
            }
        }
    }
    pthread_exit((void*)NULL);
}

int main( int argc, char** argv )
{
    int lin1, col1, lin2, col2;
	double time1, time2;
	
	thread_arg a[NUM_THREADS];
	pthread_t tid[NUM_THREADS];
	int i = 0, j = 0;
	
	time1 = omp_get_wtime();
    matriz_1 = matriz2d_alloc( "matriz1.dat", &lin1, &col1 );
	matriz_2 = matriz2d_alloc( "matriz2.dat", &lin2, &col2 );
	matriz_3 = matriz2d_alloc_vazio( lin1, col2 );
	time2 = omp_get_wtime();
	printf("Tempo gasto para ler do disco e alocar memória: %f\n", time2 - time1 );
	printf("Matriz1 linhas: %d, colunas: %d, Matriz2 linhas: %d, colunas: %d\n", lin1, col1, lin2, col2 );

	//matriz2d_print( matriz_1, 4, 3 );
	printf( "\n" );
	//matriz2d_print( matriz_2, lin2, col2 );
    
    //Inicialização da variável qtdLinhas
    for(i = 0; i < NUM_THREADS; i++){
        a[i].qtdLinhas = 0;
    }
    i = 0;
    
    //Distribuição de carga para as threads.
    while(i < lin1){
        if(j >= NUM_THREADS){
            j = 0;
        }
        a[j].qtdLinhas += 1;
        j++;
        i++;
    }
    j = 0;
    
	//Multiplicando Matrizes.
	time1 = omp_get_wtime();
	for(i = 0; i < NUM_THREADS; i++){
	    a[i].linhas1 = lin1;
	    a[i].linhas2 = lin2;
	    a[i].colunas1 = col1;
	    a[i].colunas2 = col2;
        a[i].inicio = j;
        j += a[i].qtdLinhas;
        a[i].fim = j;
        
		pthread_create(&tid[i], NULL, matriz2d_multiplica,(void*)&a[i]);
	}

	for(i = 0; i < NUM_THREADS; i++){
		pthread_join(tid[i], NULL);
	}	
	time2 = omp_get_wtime();	
	printf("Tempo gasto na operação de multiplicação: %f\n", time2 - time1 );
	
	time1 = omp_get_wtime();
	matriz2d_save_to_file( "matriz_resultado_multi.dat", matriz_3, lin1, col2 );
	time2 = omp_get_wtime();
	printf("Tempo gasto salvar no disco: %f\n", time2 - time1 );

	time1 = omp_get_wtime();
	matriz2d_free( matriz_1, lin1 );
	matriz2d_free( matriz_2, lin2 );
	matriz2d_free( matriz_3, lin1 );
	time2 = omp_get_wtime();
	printf("Tempo gasto para desalocar memória: %f\n", time2 - time1 );
    
    pthread_exit((void*)NULL);
    
    return (EXIT_SUCCESS );
}
