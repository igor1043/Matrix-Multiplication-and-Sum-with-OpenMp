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
    int **matriz1 = matriz2d_alloc_vazio(3, 3);
    
    matriz1[0][0] = 1;
    matriz1[0][2] = 2;
    matriz2d_print(matriz1, 3, 3);
    
    //liberando memória.
    matriz2d_free(matriz1, 3);
    
    return (EXIT_SUCCESS );
}

