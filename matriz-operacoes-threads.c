#include "matriz-operacoes-threads.h"


/*
function somarIJ
Realiza a soma de duas Matrizes ( Inicio pela Matriz A )

@return int, Sempre 0

@param **aMatrizA, pointer, Ponteiro que representa a Matriz A
@param **aMatrizB, pointer, Ponteiro que representa a Matriz B
@param **aMatrizC, pointer, Ponteiro que representa a Matriz C
@param nLinA, int, Numero de Linhas da Matriz A
@param nColA, int, Numero de Colunas da Matriz A
@param nLinB, int, Numero de Linhas da Matriz B
@param nColB, int, Numero de Colunas da Matriz B
*/
int somarIJ (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB) {
  
  vldAlloc(aMatrizA, aMatrizB, aMatrizC);

  vldMatriz(nColA,nLinB,nLinA,nColB,2);

  // Percorre todas as Linhas da Matriz A
  for (int nCntLin=0; nCntLin < nLinA; nCntLin++)
    // Percorre todas as Colunas da Matriz B
    for (int nCntCol=0; nCntCol < nColB; nCntCol++)
      aMatrizC[nCntLin][nCntCol] = aMatrizA[nCntLin][nCntCol] + aMatrizB[nCntLin][nCntCol];

  return 0;
}

/*
function multiplicarIKJ
Realiza a Multiplicação de duas Matrizes 
Ordem: Linha Matriz A > Coluna A\Linha B > Coluna Matriz B

@return int, Sempre 0

@param **aMatrizA, pointer, Ponteiro que representa a Matriz A
@param **aMatrizB, pointer, Ponteiro que representa a Matriz B
@param **aMatrizC, pointer, Ponteiro que representa a Matriz C
@param nLinA, int, Numero de Linhas da Matriz A
@param nColA, int, Numero de Colunas da Matriz A
@param nColB, int, Numero de Colunas da Matriz B
@param nLinB, int, Numero de Linhas da Matriz B
*/
int multiplicarIKJ (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB) {

  // Valida se Matriz foi alocada
  vldAlloc(aMatrizA, aMatrizB, aMatrizC);
  
  // Valida se estrutura da Matriz foi respeitada
  vldMatriz(nColA,nLinB,nLinA,nColB,1);
  
  // Percorre Linha de A
  for (int nCntLA=0; nCntLA < nLinA; nCntLA++ )
    // Percorre Coluna A = Linha B
    for (int nCntLX=0; nCntLX < nColA; nCntLX++ )
      // Percorre Coluna de B
      for (int nCntCB=0; nCntCB < nColB; nCntCB++ )
        aMatrizC[nCntLA][nCntCB] += aMatrizA[nCntLA][nCntLX] * aMatrizB[nCntLX][nCntCB];

  return 0;
}
/*
function multiplicarIKJThread
Realiza a Multiplicação de duas Matrizes em Thread
Ordem: Linha Matriz A > Coluna A\Linha B > Coluna Matriz B

@return int, Sempre 0

@param **aMatrizA, pointer, Ponteiro que representa a Matriz A
@param **aMatrizB, pointer, Ponteiro que representa a Matriz B
@param **aMatrizC, pointer, Ponteiro que representa a Matriz C
@param nLinA, int, Numero de Linhas da Matriz A
@param nColA, int, Numero de Colunas da Matriz A
@param nColB, int, Numero de Colunas da Matriz B
@param nLinB, int, Numero de Linhas da Matriz B
*/
int multiplicarIKJThread (int **aMatrizA, int **aMatrizB, int **aMatrizC, int nLinA, int nColA, int nColB, int nLinB, int nThread, int nMaxThread) {

  // Valida se Matriz foi alocada
  vldAlloc(aMatrizA, aMatrizB, aMatrizC);
  
  // Valida se estrutura da Matriz foi respeitada
  vldMatriz(nColA,nLinB,nLinA,nColB,1);
  
  // Percorre Linha de A
  for (int nCntLA=nThread; nCntLA < nLinA; nCntLA += nMaxThread )
    // Percorre Coluna A = Linha B
    for (int nCntLX=0; nCntLX < nColA; nCntLX++ )
      // Percorre Coluna de B
      for (int nCntCB=0; nCntCB < nColB; nCntCB++ )
        aMatrizC[nCntLA][nCntCB] += aMatrizA[nCntLA][nCntLX] * aMatrizB[nCntLX][nCntCB];

  return 0;
}

/*
function vldAlloc
Valida alocação das Matrizes

@param **aMatrizA, pointer, Ponteiro que representa a Matriz A
@param **aMatrizB, pointer, Ponteiro que representa a Matriz B
@param **aMatrizC, pointer, Ponteiro que representa a Matriz C
*/
void vldAlloc(int **aMatrizA, int **aMatrizB, int **aMatrizC){
  if(aMatrizA == NULL || aMatrizB == NULL || aMatrizC == NULL){
    printf("==== Matrizes não alocadas corretamente ====\n");
    exit(1);
  }
}

/*
function vldMatriz
Valida Matriz para Realização da Operação

@param nColA, int, Valor de Lado na Matriz A
@param nLinB, int, Valor de Lado na Matriz B
@param nLinA, int, Valor de N na Matriz A
@param nColB, int, Valor de M na Matriz B
@param nOperation, int, Operação a ser realizada
*/
void vldMatriz(int nColA, int nLinB, int nLinA, int nColB, int nOperation){
	// Restricao da operacao de soma de matrizes
	// Numero de linha de matriz_a deve ser o mesmo de colunas da matriz_b
	if (nOperation == 1){
		if (nColA != nLinB){
			printf("ERROR: Matriz A vs Matriz B incompatíveis.\n");
			exit(1);
		}
	}else if( nOperation == 2){
		if(nColA != nColB || nLinA != nLinB ) {
			printf("ERROR: Matriz A vs Matriz B incompatíveis para Soma.\nOperação de Soma não será realizada.\n");
			exit(1);
		}
	}
}

/*
function multiplicar_submatriz
Realiza a Multiplicação de Sub Matriz

@return int, Sempre 0

@param *mat_suba, pointer, Ponteiro que representa a Matriz A
@param *mat_subb, pointer, Ponteiro que representa a Matriz B
@param *mat_subc, pointer, Ponteiro que representa a Matriz C
*/
int multiplicar_submatriz (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc) {
  // Realiza a multiplicação da Sub Matriz
  multiplicarIKJ(mat_suba->matriz,mat_subb->matriz,mat_subc->matriz,mat_suba->bloco->lin_fim,mat_suba->bloco->col_fim,mat_subb->bloco->col_fim,mat_subb->bloco->lin_fim);
	return 0;
}