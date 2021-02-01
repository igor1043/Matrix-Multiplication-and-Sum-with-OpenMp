#ifndef MATRIZ2D_H
#define	MATRIZ2D_H

#ifdef	__cplusplus
extern "C" {
#endif

//imprime matriz na tela
void matriz2d_print(int **, int, int);

//Aloca matriz na memória a partir de um arquivo.
int** matriz2d_alloc(char *, int*, int*);

//Aloca uma matriz vazia(com valores 0) na memória
int** matriz2d_alloc_vazio(int, int);

//Aloca uma matriz vazia(com valores 0) na memória
int** matriz2d_alloc_rand(int, int);

//Salva da memória para o disco.
int matriz2d_save_to_file(char*, int**, int, int);

//Libera espaço de memória da matriz
void matriz2d_free(int **, int);

//Soma duas matrizes em uma terceira matriz.
void *matriz2d_soma(int **, int **, int **, int, int);

//Multiplica duas matrizes e uma terceira matriz.
void matriz2d_multiplica(int **, int **, int **, int, int, int, int);

#ifdef	__cplusplus
}
#endif

#endif	/* MATRIZ2D_H */

