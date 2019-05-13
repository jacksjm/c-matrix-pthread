#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matriz.h"

void vldAlloc(int **aMatrizA, int **aMatrizB, int **aMatrizC);

void vldMatriz(int nLa, int nLb, int nN, int nM, int nOperation);

int somarIJ (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB);
int multiplicarIKJ (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB);
int multiplicarIKJThread (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB, int nThread, int nMaxThread);

int multiplicar_submatriz (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc);
int multiplicar_submatrizThread (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc);