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
    int lin = 3000, col = 4000;
    int **matriz_1 = NULL;

    if ( argc != 4 ) {
      printf( "Uso incorreto\n" );
      printf( "Maneira de usar:\n" );
      printf( "main_gera_matriz <nunLinhas> <nunColunas> <nomeArquivo>\n" );
      
    }
    else {
      lin = atoi(argv[1]);
      col = atoi(argv[2]);
      //matriz2d_print( matriz_1, 4, 3 );
      printf( "\n" );
      //matriz2d_print( matriz_2, lin2, col2 );
      
      printf( "<nunLinhas=%d> <nunColunas=%d> <nomeArquivo=%s>\n", lin, col, argv[3] );
      matriz_1 = matriz2d_alloc_rand( lin, col );

      //Multiplicando Matrizes.
      matriz2d_save_to_file( argv[3], matriz_1, lin, col );
      matriz2d_free( matriz_1, lin );
    }
    return (EXIT_SUCCESS );
}
