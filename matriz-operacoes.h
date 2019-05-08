#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matriz.h"

void vldAlloc(int **aMatrizA, int **aMatrizB, int **aMatrizC);

void vldMatriz(int nLa, int nLb, int nN, int nM, int nOperation);

int somarIJ (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB);
int somarJI (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB);

int multiplicarIJK (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB);
int multiplicarIKJ (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB);

int multiplicarKIJ (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB);
int multiplicarJIK (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB);

int multiplicarJKI (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB);
int multiplicarKJI (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB);

int multiplicar_submatriz (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc);