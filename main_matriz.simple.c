#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv2.h"
#include "matriz.h"
#include "matriz-operacoes.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char *argv[]) {

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// DECLARAÇÃO de VARIÁVEIS
	int **mat_a = NULL;
	int **mat_b = NULL;
	int **matSumIJ = NULL;
	int **matSumJI = NULL;
	int **matMulIJK = NULL;
	int **matMulIKJ = NULL;
	int **matMulKJI = NULL;
	int **matMulKIJ = NULL;
	int **matMulJIK = NULL;
	int **matMulJKI = NULL;
	float nSumIJ = 0.0, nSumJI = 0.0;
	float nRunIJK = 0.0, nRunIKJ = 0.0;
	float nRunJIK = 0.0, nRunJKI = 0.0;
	float nRunKJI = 0.0, nRunKIJ = 0.0;
	FILE *fmat_a, *fmat_b;
	FILE *fmat_c;
	//*fmatbloco_c;
	int nr_line;
	int *vet_line = NULL;
	int N, M, La, Lb;
	double start_time, end_time;
	int lSoma = 1;
	int nOperation = 0;
	int nSum = 0;

	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	if (argc != 4){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b> <operation>\n", argv[0]);
		exit (1);
	}
	
  // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	fmat_a = fopen(argv[1],"r");
	fmat_b = fopen(argv[2],"r");
	if ((fmat_a == NULL) || (fmat_b == NULL)) {
		printf("Error: Na abertura dos arquivos.");
		exit(1);
	}
	nOperation = atoi(argv[3]);
	if (nOperation < 1 || nOperation > 11) {
		printf("Operação Inválida.");
		exit(1);
	}
    // matriz_a N (linha) x La (coluna)
	extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
	mat_a = alocar_matriz(N, La);
	filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);

	// matriz_b Lb (linha) x M (coluna)
	extrai_parametros_matriz(fmat_b, &Lb, &M, &vet_line, &nr_line);
	mat_b = alocar_matriz(Lb, M);
	filein_matriz (mat_b, Lb, M, fmat_b, vet_line, nr_line);
	
	if ((mat_b == NULL) || (mat_a == NULL)) {
		printf("ERROR: Out of memory\n");
	}
	
	printf("\t\t**** Loaded mat_a NxL(%d,%d) **** \n", N, La);
	imprimir_matriz(mat_a, N, La);
	printf("\t\t**** Loaded mat_b LxM(%d,%d) **** \n", Lb, M);
	imprimir_matriz(mat_b, Lb, N);
	
	if (lSoma == 1){
		if (nOperation == 1 || nOperation == 9 || nOperation == 11){
			matSumIJ = alocar_matriz(N, M);
			start_time = wtime();
			somarIJ(mat_a,mat_b,matSumIJ,N,La,M,Lb);
			end_time = wtime();
			printf("\n ##### Soma de Matrizes (IJ) #####\n");
			imprimir_matriz(matSumIJ, N, M);
			nSumIJ = end_time - start_time;
			fmat_c= fopen("somarIJ.map-result","w");
			fileout_matriz(matSumIJ, N, M, fmat_c);
			printf("\tRuntime Soma IJ: %f\n", nSumIJ);
		}

		if (nOperation == 2 || nOperation == 9 || nOperation == 11){
			matSumJI = alocar_matriz(N, M);
			start_time = wtime();
			somarJI(mat_a,mat_b,matSumJI,N,La,M,Lb);
			end_time = wtime();
			printf("\n ##### Soma de Matrizes (JI) #####\n");
			imprimir_matriz(matSumJI, N, M);
			nSumJI = end_time - start_time;
			fmat_c= fopen("somarJI.map-result","w");
			fileout_matriz(matSumJI, N, M, fmat_c);
			printf("\tRuntime Soma JI: %f\n", nSumJI);
		}
	}
	if (nOperation == 3 || nOperation == 9 || nOperation == 10){
		matMulIJK = alocar_matriz(N, M);
		start_time = wtime();
		multiplicarIJK(mat_a,mat_b,matMulIJK, N, La, M, Lb);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (IJK)  #####\n");
		imprimir_matriz(matMulIJK, N, M);
		nRunIJK = end_time - start_time;
		fmat_c= fopen("multiIJK.map-result","w");
		fileout_matriz(matMulIJK, N, M, fmat_c);
		printf("\tRuntime Multiplicação IJK: %f\n", nRunIJK);
	} 
	if (nOperation == 4 || nOperation == 9 || nOperation == 10){
		matMulIKJ = alocar_matriz(N, M);
		start_time = wtime();
		zerar_matriz(matMulIKJ, N, M);
		multiplicarIKJ(mat_a,mat_b,matMulIKJ, N, La, M, Lb);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (IKJ)  #####\n");
		imprimir_matriz(matMulIKJ, N, M);
		nRunIKJ = end_time - start_time;
		fmat_c= fopen("multiIKJ.map-result","w");
		fileout_matriz(matMulIKJ, N, M, fmat_c);
		printf("\tRuntime Multiplicação IKJ: %f\n", nRunIKJ);
	} 
	if (nOperation == 5 || nOperation == 9 || nOperation == 10){
		matMulKIJ = alocar_matriz(N, M);
		start_time = wtime();
		zerar_matriz(matMulKIJ, N, M);
		multiplicarKIJ(mat_a,mat_b,matMulKIJ, N, La, M, Lb);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (KIJ)  #####\n");
		imprimir_matriz(matMulKIJ, N, M);
		nRunKIJ = end_time - start_time;
		fmat_c= fopen("multiKIJ.map-result","w");
		fileout_matriz(matMulKIJ, N, M, fmat_c);
		printf("\tRuntime Multiplicação KIJ: %f\n", nRunKIJ);
	}
	if (nOperation == 6 || nOperation == 9 || nOperation == 10){
		matMulKJI = alocar_matriz(N, M);
		start_time = wtime();
		zerar_matriz(matMulKJI, N, M);
		multiplicarKJI(mat_a,mat_b,matMulKJI, N, La, M, Lb);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (KJI)  #####\n");
		imprimir_matriz(matMulKJI, N, M);
		nRunKJI = end_time - start_time;
		fmat_c= fopen("multiKJI.map-result","w");
		fileout_matriz(matMulKJI, N, M, fmat_c);
		printf("\tRuntime Multiplicação KJI: %f\n", nRunKJI);
	}
	if (nOperation == 7 || nOperation == 9 || nOperation == 10){
		matMulJIK = alocar_matriz(N, M);
		start_time = wtime();
		multiplicarJIK(mat_a,mat_b,matMulJIK, N, La, M, Lb);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (JIK)  #####\n");
		imprimir_matriz(matMulJIK, N, M);
		nRunJIK = end_time - start_time;
		fmat_c= fopen("multiJIK.map-result","w");
		fileout_matriz(matMulJIK, N, M, fmat_c);
		printf("\tRuntime Multiplicação JIK: %f\n", nRunJIK);
	}
	if (nOperation == 8 || nOperation == 9 || nOperation == 10){
		matMulJKI = alocar_matriz(N, M);
		start_time = wtime();
		zerar_matriz(matMulJKI, N, M);
		multiplicarJKI(mat_a,mat_b,matMulJKI, N, La, M, Lb);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (JKI)  #####\n");
		imprimir_matriz(matMulJKI, N, M);
		nRunJKI = end_time - start_time;
		fmat_c= fopen("multiJKI.map-result","w");
		fileout_matriz(matMulJKI, N, M, fmat_c);
		printf("\tRuntime Multiplicação JKI: %f\n", nRunJKI);
	}
	// Imprime tempos de execução - Sumarização
	if ( nOperation >= 9 ){
		printf("Deseja visualizar uma sumarização dos dados? [1=Sim] ");
		if (scanf("%d",&nSum) == 1 && nSum == 1){
			printf("\n\n");
			printf("\t==== SUMARIZAÇÃO ====\n");
			// Imprime comparação e Runtime das Somas
			if ( nOperation != 10 ){
				printf("\n\n");
				printf("\tRuntime Soma IJ: %f\n", nSumIJ);
				printf("\tRuntime Soma JI: %f\n", nSumJI);
				comparar_matriz(matSumIJ,matSumJI,N,M);
			}
			// Imprime comparação e Runtime das Multiplicações
			if ( nOperation != 11){
				printf("\n\n");
				printf("\tRuntime Multiplicação IJK: %f\n", nRunIJK);
				printf("\tRuntime Multiplicação IKJ: %f\n", nRunIKJ);
				printf("\tRuntime Multiplicação KIJ: %f\n", nRunKIJ);
				printf("\tRuntime Multiplicação KJI: %f\n", nRunKJI);
				printf("\tRuntime Multiplicação JIK: %f\n", nRunJIK);
				printf("\tRuntime Multiplicação JKI: %f\n", nRunJKI);

				printf("\n\n");
				printf("\tComparações IJK: \n");
				printf("\tComparações IKJ: \n");
				comparar_matriz(matMulIJK,matMulIKJ,N,M);
				printf("\tComparações KIJ: \n");
				comparar_matriz(matMulIJK,matMulKIJ,N,M);
				printf("\tComparações KJI: \n");
				comparar_matriz(matMulIJK,matMulKJI,N,M);
				printf("\tComparações JIK: \n");
				comparar_matriz(matMulIJK,matMulJIK,N,M);
				printf("\tComparações JKI: \n");
				comparar_matriz(matMulIJK,matMulJKI,N,M);

				printf("\n\n");
				printf("\tComparações IKJ: \n");
				printf("\tComparações KIJ: \n");
				comparar_matriz(matMulIKJ,matMulKIJ,N,M);
				printf("\tComparações KJI: \n");
				comparar_matriz(matMulIKJ,matMulKJI,N,M);
				printf("\tComparações JIK: \n");
				comparar_matriz(matMulIKJ,matMulJIK,N,M);
				printf("\tComparações JKI: \n");
				comparar_matriz(matMulIKJ,matMulJKI,N,M);

				printf("\n\n");
				printf("\tComparações KIJ: \n");
				printf("\tComparações KJI: \n");
				comparar_matriz(matMulKIJ,matMulKJI,N,M);
				printf("\tComparações JIK: \n");
				comparar_matriz(matMulKIJ,matMulJIK,N,M);
				printf("\tComparações JKI: \n");
				comparar_matriz(matMulKIJ,matMulJKI,N,M);

				printf("\n\n");
				printf("\tComparações KJI: \n");
				printf("\tComparações JIK: \n");
				comparar_matriz(matMulKJI,matMulJIK,N,M);
				printf("\tComparações JKI: \n");
				comparar_matriz(matMulKJI,matMulJKI,N,M);

				printf("\n\n");
				printf("\tComparações JIK: \n");
				printf("\tComparações JKI: \n");
				comparar_matriz(matMulJIK,matMulJKI,N,M);
			}
		}else{
			printf("\tSumarização descartada.\n");
		}
	}


	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	liberar_matriz(mat_a,N,La);
	liberar_matriz(mat_b,Lb,M);
	liberar_matriz(matMulIJK,N,M);
	liberar_matriz(matMulIKJ,N,M);
	liberar_matriz(matMulKJI,N,M);
	liberar_matriz(matMulKIJ,N,M);
	liberar_matriz(matMulJIK,N,M);
	liberar_matriz(matMulJKI,N,M);

	fclose(fmat_a);
	fclose(fmat_b);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	return 0;
}
