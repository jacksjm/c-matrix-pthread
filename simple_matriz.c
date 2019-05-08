#define N 10
#define M 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"

int main(int argc, char *argv[]) {

    int **mat_a = NULL;
    mat_a = alocar_matriz(N, M);
    imprimir_matriz(mat_a, N, M);
    zerar_matriz(mat_a, N, M);
    imprimir_matriz(mat_a, N, M);
    gerar_matriz(mat_a, N, M, -9999);
    imprimir_matriz(mat_a, N, M);
    liberar_matriz(mat_a, N, M);
    return 0;

}