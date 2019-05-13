#include "matriz.h"
#include "toolsv2.h"

/*
function gerar_matriz
Gera valores dentro de uma Matriz já alocada

@return int, Sempre 0

@param **aMatriz, pointer, Ponteiro que representa a Matriz
@param nLinha, int, Numero de Linhas da Matriz
@param nColuna, int, Numero de Colunas da Matriz
@param nValor, int, Indica o valor a ser gerado: 
						-9999 	- Aleatório
						-8888 	- Valores crescentes
						-7777 	- Valores decrescentes
						0 		- Valores zerados
*/
int gerar_matriz(int **aMatriz, int nLinha, int nColuna, int nValor){
	
	int nInput = 0;// Controlador de valor

	srand(time(NULL));
	
	if ( aMatriz == NULL ){
		printf("==== Matriz não alocada ====\n");
		exit(1);
	}
	// Percorre todas as Linhas da Matriz
	for (int nCntLin=0; nCntLin < nLinha; nCntLin++) {
		// Percorre todas as Colunas da Matriz
		for (int nCntCol=0; nCntCol < nColuna; nCntCol++) {

			// Verifica o valor passado por parâmetro
			switch (nValor)
			{
				case -9999: // Aleatoriza um valor de 0 a 100
					nInput = rand() % 100;
					break;
				case -8888: // Atribui o valor da linha
					nInput = nCntLin;
					break;
				case -7777: // Atribui um valor decrescente a linha
					nInput = nLinha - nCntLin;
					break;
				case 0: // Zera os valores
					nInput = 0;
					break;
				default:// Define como valor padrão o passado no parâmetro
					nInput = nValor;
					break;
			}
			// Atribui o valor a posição da Matriz
			aMatriz[nCntLin][nCntCol] = nInput;
		}
	}
	return 0;
}

/*
function zerar_matriz
Gera valores zerados em uma Matriz já alocada

@return int, Sempre 0

@param **aMatriz, pointer, Ponteiro que representa a Matriz
@param nLinha, int, Numero de Linhas da Matriz
@param nColuna, int, Numero de Colunas da Matriz
*/
int zerar_matriz (int **aMatriz, int nLinha, int nColuna){
	if ( aMatriz == NULL ){
		printf("==== Matriz não alocada ====\n");
		exit(1);
	}
	// Chama a geração Zerando os valores
	return gerar_matriz(aMatriz,nLinha,nColuna,0);
}

/*
function imprimir_matriz
Imprime os valores da Matriz

@return int, Sempre 0

@param **aMatriz, pointer, Ponteiro que representa a Matriz
@param nLinha, int, Numero de Linhas da Matriz
@param nColuna, int, Numero de Colunas da Matriz
*/
int imprimir_matriz (int **aMatriz, int nLinha, int nColuna){

	if ( aMatriz == NULL ){
		printf("==== Matriz não alocada ====\n");
		exit(1);
	}

	// Realiza uma impressão de primeira linha com posição das colunas
	for (int nCntCol=0; nCntCol < nColuna; nCntCol++)
		printf("\t(%d)", nCntCol);

	// Pula linha
	printf("\n");

	// Percorre as linhas da Matriz
	for (int nCntLin=0; nCntLin < nLinha; nCntLin++) {
		// Imprime no começo da linha a posição
		printf("(%d)", nCntLin);
		// Percorre as colunas da Matriz
	  	for (int nCntCol=0; nCntCol < nColuna; nCntCol++){
			// Imprime os valores contidos na Matriz
			printf("\t%d", aMatriz[nCntLin][nCntCol]);
		}
		printf("\n");
	}
	return 0;
}

/*
function comparar_matriz
Realiza a comparação de duas Matrizes

@return int, Sempre 0

@param **aMatrizA, pointer, Ponteiro que representa a Matriz A
@param **aMatrizB, pointer, Ponteiro que representa a Matriz B
@param nLinha, int, Numero de Linhas da Matriz
@param nColuna, int, Numero de Colunas da Matriz
*/
int comparar_matriz (int **aMatrizA, int **aMatrizB, int nLinha, int nColuna){
	double nStartTime, nEndTime;

	if ( aMatrizA == NULL ){
		printf("==== Matriz A não alocada ====\n");
		exit(1);
	}

	if ( aMatrizB == NULL ){
		printf("==== Matriz B não alocada ====\n");
		exit(1);
	}

	nStartTime = wtime();
	for (int nCntLin=0; nCntLin < nLinha; nCntLin++) {
	  for (int nCntCol=0; nCntCol < nColuna; nCntCol++){
			if (aMatrizA[nCntLin][nCntCol] != aMatrizB[nCntLin][nCntCol]) {
				printf("O elemento [%d,%d] é diferente nas matrizes analisadas!\n", nCntLin,nCntCol);
				return 1;
			}
		}

	}
	nEndTime = wtime();
	printf("VERIFICADO: Matrizes identicas\n");
	printf("Runtime: %f\n", nEndTime - nStartTime);
	return 0;
}

/*
function liberar_matriz
Imprime os valores da Matriz

@return int, Sempre nulo

@param **aMatriz, pointer, Ponteiro que representa a Matriz
@param nLinha, int, Numero de Linhas da Matriz
@param nColuna, int, Numero de Colunas da Matriz
*/
int **liberar_matriz (int **aMatriz, int nLinha, int nColuna) {
	
	// Só necessita liberar Matrizes alocadas
	if (aMatriz) {
		// Libera as posições de cada Linha
		for (int i =0; i < nLinha; i++)
			free(aMatriz[i]);

		// Libera a Matriz completa
		free(aMatriz);
	}

	return NULL;
}

/*
function alocar_matriz
Realiza a alocação dos espaços de Memória

@return pointer, Ponteiro (Matriz) alocado

@param nLinha, int, Numero de Linhas da Matriz
@param nColuna, int, Numero de Colunas da Matriz
*/
int **alocar_matriz (int nLinha, int nColuna) {
  int **aNovaMatriz = NULL;

	aNovaMatriz = (int **) malloc(nLinha * sizeof(int *));
	if (!aNovaMatriz) {
		printf("ERROR: Out of memory\n");
		return NULL;
	}

  	for (int i =0; i < nLinha; i++) {
			aNovaMatriz[i] = (int *) malloc(sizeof(int)*nColuna);
			if (!aNovaMatriz) {
				printf("ERROR: Out of memory\n");
				return NULL;
			}
	}
	return aNovaMatriz;
}
/*
function gerar_submatriz
Realiza a Cópia da Matriz Original para a Sub Matriz

@return integer, Sempre zero

@param **mat_origem, pointer, Ponteiro para a Matriz Origem
@param **submatriz, pointer, Ponteiro para a Sub Matriz que será alimentada
@param **bloco, pointer, Ponteiro para as Informações da Matriz Origem
*/
int gerar_submatriz (int **mat_origem, int **submatriz, bloco_t *bloco) {
  
	int nCntCol = 0;
	int nCntLin = 0;

	// Percorre a matriz origem para alimentar os valores da Sub Matriz
	for (int nLin=bloco->lin_inicio;nLin<bloco->lin_fim;nLin++)
		{
		for (int nCol=bloco->col_inicio;nCol<bloco->col_fim;nCol++)
			{
				submatriz[nCntLin][nCntCol] = mat_origem[nLin][nCol];
				nCntCol += 1;
			}
			nCntLin += 1;
			nCntCol = 0;
	}
  	return 0;
}
/*
function particionar_matriz
Realiza a Cópia da Matriz Original para a Sub Matriz

@return pointer, Ponteiro para as Sub Matrizes Geradas

@param **matriz, pointer, Ponteiro para a Matriz Origem
@param mat_lim, integer, Valor de Linha da Matriz
@param mat_col, integer, Valor de Coluna da Matriz
@param orientacao, integer, Corte que será realizado (0 - horizontal, 1 - vertical)
@param nro_submatrizes, integer, Número de Sub Matrizes a serem geradas
*/
matriz_bloco_t **particionar_matriz (int **matriz, int mat_lin, int mat_col, int orientacao, int nro_submatrizes) {
	
	matriz_bloco_t **aSubMat = malloc( nro_submatrizes * sizeof(matriz_bloco_t *));

	int nTamLim = orientacao == 1? mat_col : mat_lin;
    int nTamCar = 1;
	int nResto = 0;
	int nUseRes = 0;
	int nLastEnd = 0;

	// Define uma Distribuição de Carga Simples
	// Enquanto o tamanho de cada carga multiplicado pela
	// quantidade de processamentos for menor que o limite
	// alimenta a carga
	nTamCar = nTamLim/nro_submatrizes;


	// Verifica se há "resto" de alocação
	if ( nTamCar * nro_submatrizes < nTamLim){
		nResto = nTamLim - ( nTamCar * nro_submatrizes );
	}

	// Se carga estiver zerada, há mais processamentos que limites
	if (nTamCar == 0) {
		printf("Há mais processamentos do que submatrizes, favor rever quantidade de processos.\n");
		exit(1);
	}else{
		for(int nSubMat=0;nSubMat<nro_submatrizes;nSubMat++){

			// Distribui o resto de carga
			if ( nResto != 0 ){
				nUseRes = 1;
				nResto -= 1;
			}else{
				nUseRes = 0;
			}

			// Aloca um Bloco do Tipo bloco_t para utilização
			bloco_t *blocoX = malloc(sizeof(bloco_t));
			// Gera o Bloco para busca da SubMatriz
			blocoX->col_inicio = 0;
			blocoX->col_fim = mat_col;
			blocoX->lin_inicio = 0;
			blocoX->lin_fim = mat_lin;
			if (orientacao == 1){
				blocoX->col_inicio = nLastEnd;
				blocoX->col_fim = nLastEnd + nTamCar + nUseRes;
			}else{
				blocoX->lin_inicio = nLastEnd;
				blocoX->lin_fim = nLastEnd + nTamCar + nUseRes;
			}
			nLastEnd += nTamCar + nUseRes;

			// Aloca uma Matriz para utilização
			int **matrizX;
			if (orientacao ==1){
				matrizX = alocar_matriz(mat_lin, nTamCar + nUseRes);
				zerar_matriz(matrizX, mat_lin, nTamCar + nUseRes);
			}else{
				matrizX = alocar_matriz(nTamCar + nUseRes, mat_col);
				zerar_matriz(matrizX, nTamCar + nUseRes, mat_col);
			}
			
			// Gera a SubMatriz com base nos dados da Matriz Principal
			// e as posições da contagem de corte
			gerar_submatriz(matriz,matrizX,blocoX);

			// Gera o Bloco com o tamanho correto da Matriz
			blocoX->col_inicio = 0;
			blocoX->col_fim = mat_col;
			blocoX->lin_inicio = 0;
			blocoX->lin_fim = mat_lin;
			if (orientacao ==1){
				blocoX->col_fim = nTamCar + nUseRes;
			}else{
				blocoX->lin_fim = nTamCar + nUseRes;
			}
			
			// Salva as alocações na matriz de retorno
			aSubMat[nSubMat] = (matriz_bloco_t *) malloc(sizeof(matriz_bloco_t));
			aSubMat[nSubMat]->bloco = blocoX;
			aSubMat[nSubMat]->matriz = matrizX;
		}
	}

  return aSubMat;
}

/*
function constroi_submatrizv2
Controi a Matriz que receberá as operações de Multiplicação das Sub Matrizes

@return pointer, Ponteiro para a Matriz

@param mat_lim, integer, Valor de Linha da Matriz
@param mat_col, integer, Valor de Coluna da Matriz
@param divisor, integer, Número de Sub Matrizes a serem geradas
*/
matriz_bloco_t **constroi_submatrizv2 (int mat_lin, int mat_col, int divisor) {

	// Aloca o espaço de Memória para o Vetor de Matrizes
	matriz_bloco_t **aSubMat = malloc( divisor * sizeof(matriz_bloco_t *));

	// Percorre o número de divisores
	for(int nSubMat=0;nSubMat<divisor;nSubMat++){

		// Cria um bloco para receber os valores
		bloco_t *blocoX = malloc(sizeof(bloco_t));
		blocoX->col_inicio = 0;
		blocoX->col_fim = mat_col;
		blocoX->lin_inicio = 0;
		blocoX->lin_fim = mat_lin;
		
		// Cria a Matriz principal alocada e zerada
		int **matrizX = alocar_matriz(mat_lin,mat_col);
		zerar_matriz(matrizX,mat_lin,mat_col);

		// Adiciona a Matriz de Retorno
		aSubMat[nSubMat] = (matriz_bloco_t *) malloc(sizeof(matriz_bloco_t));
		aSubMat[nSubMat]->bloco = blocoX;
		aSubMat[nSubMat]->matriz = matrizX;
	}

	return aSubMat;
}

/*
function liberar_submatriz
Libera as Matrizes de Sub Matriz

@return NULL, Sempre nulo

@param **submatriz, pointer, Ponteiro para a Matriz
@param nro_submatriz, integer, Número de Sub Matrizes geradas
*/
matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz, int nro_submatriz) {

  // Percorre as submatrizes
  for(int nCnt=0;nCnt<nro_submatriz;nCnt++){
	  // Libera a Matriz
	  liberar_matriz(submatriz[nCnt]->matriz,submatriz[nCnt]->bloco->lin_fim,submatriz[nCnt]->bloco->col_fim);

	  // Libera o Bloco
	  free(submatriz[nCnt]->bloco);

	  // Libera o Objeto de Sub Matrizes
	  free(submatriz[nCnt]);
  }
  
  // Libera o Vetor de Matrizes
  free(submatriz);

  return NULL;
}