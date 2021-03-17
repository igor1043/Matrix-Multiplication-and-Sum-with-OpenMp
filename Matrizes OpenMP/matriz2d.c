/*
* Author:  Igor Vinicius Freitas de Souza
* GitHub: https://github.com/igor1043
* E-mail: igorviniciusfreitasouza@gmail.com
*/
#include "matriz2d.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

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

void matriz2d_soma(int ** matriz1, int ** matriz2, int ** matriz3, int lin, int col)
{
    int i, j;

    #pragma omp parallel for private(j)
    for (i = 0; i < lin; i++){
        for (j = 0; j < col; j++){
            matriz3[i][j] = matriz1[i][j] + matriz2[i][j];
        }
    }
}

void matriz2d_multiplica(int ** matriz1, int ** matriz2, int ** matriz3,
                         int lin1, int col1, int lin2, int col2)
{
    int i, j, k;

    if ( col1 != lin2 ) {
        fprintf(stderr, "Não é possível multiplicar as matrizes\n");
        exit(EXIT_FAILURE);
    }

    #pragma omp parallel for private (j,k)
    for (i = 0; i < lin1; i++){
        for (j = 0; j < col2; j++){
            for (k = 0; k < col1; k++){
                matriz3[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }
}
