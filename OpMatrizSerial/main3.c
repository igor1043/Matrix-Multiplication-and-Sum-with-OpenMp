/*
* Author:  Igor Vinicius Freitas de Souza
* GitHub: https://github.com/igor1043
* E-mail: igorviniciusfreitasouza@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>
#include "matriz2d.h"

int main( int argc, char** argv )
{
    int lin1, col1, lin2, col2;
    int **matriz1 = matriz2d_alloc("matriz1.dat", &lin1, &col1);
    int **matriz2 = matriz2d_alloc("matriz2.dat", &lin2, &col2);
    int **matriz3 = matriz2d_alloc_vazio(lin1, col1);
    
    matriz2d_print(matriz1, lin1, col1);
    printf("\n");
    matriz2d_print(matriz2, lin2, col2);
    
    //multiplica matrizes
    matriz2d_multiplica(matriz1, matriz2, matriz3, lin1, col1, lin2, col2);
    printf("\n");
    matriz2d_print(matriz3, lin1, col1);
    
    //liberando memória.
    matriz2d_free(matriz1, lin1);
    matriz2d_free(matriz2, lin2);
    matriz2d_free(matriz3, lin1);
    
    return (EXIT_SUCCESS );
}
