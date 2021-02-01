#include <stdio.h>
#include <stdlib.h>
#include "matriz2d.h"

int main( int argc, char** argv )
{
    int lin = 3000, col = 4000;
    int **matriz_1 = matriz2d_alloc_rand( lin, col );

    //matriz2d_print( matriz_1, 4, 3 );
    printf( "\n" );
    //matriz2d_print( matriz_2, lin2, col2 );

    //Multiplicando Matrizes.
    matriz2d_save_to_file( "matriz_resultado1.dat", matriz_1, lin, col );
    matriz2d_free( matriz_1, lin );
    return (EXIT_SUCCESS );
}
