#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "toolsv2.h"
#include "matriz.h"
#include "matriz-operacoes-threads.h"

int **mat_a = NULL;
int **mat_b = NULL;
int **mat_c = NULL;
int **mat_c_thread = NULL;
int **mat_c_bloco = NULL;
int **mat_c_bloco_thread = NULL;
int N, M, La, Lb;
matriz_bloco_t **Vsubmat_a = NULL;
matriz_bloco_t **Vsubmat_b = NULL;
matriz_bloco_t **Vsubmat_c = NULL;

typedef struct {
      int tid;
      int ntasks;
} param_t;

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void *execMultThread (void *arg) {
  param_t *p = (param_t *) arg;

  multiplicarIKJThread(mat_a,mat_b,mat_c_thread, N, La, M, Lb, p->tid, p->ntasks);
  return NULL;
}

void *execMultBlocoThread (void *arg) {
  param_t *p = (param_t *) arg;

  multiplicar_submatriz (Vsubmat_a[p->tid], Vsubmat_b[p->tid], Vsubmat_c[p->tid]);
  return NULL;
}

int main(int argc, char *argv[]) {
    
    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// DECLARAÇÃO de VARIÁVEIS
	
	FILE *fmat_a, *fmat_b;
	FILE *fmat_c;
	int nr_line;
	int *vet_line = NULL;
    int nMaxThread;
    int nCnt;
    int nLimit = 10;
    int nBlocos = 20;
    int nMulti = 0;
    int nJoin = 0;
	double nStartTime, nEndTime;
    double nTimeIKJ = 0.0;
    double nTimeIKJThread = 0.0;
    double nTimeBloco = 0.0;
    double nTimeBlocoThread = 0.0;
    double nMidIKJ, nMidBloco;
    double nMidIKJThread, nMidBlocoThread;
    param_t *args;
    pthread_t *threads;

	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	if (argc != 4){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b> <thread>\n", argv[0]);
		exit (1);
	}
	
    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	fmat_a = fopen(argv[1],"r");
	fmat_b = fopen(argv[2],"r");
	if ((fmat_a == NULL) || (fmat_b == NULL)) {
		printf("Error: Na abertura dos arquivos.");
		exit(1);
	}
	nMaxThread = atoi(argv[3]);
    threads = (pthread_t *) malloc(nMaxThread * sizeof(pthread_t));
    args = (param_t *) malloc(nMaxThread * sizeof(param_t));
    
    // matriz_a N (linha) x La (coluna)
	extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
	mat_a = alocar_matriz(N, La);
	filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);

	// matriz_b Lb (linha) x M (coluna)
	extrai_parametros_matriz(fmat_b, &Lb, &M, &vet_line, &nr_line);
	mat_b = alocar_matriz(Lb, M);
	filein_matriz (mat_b, Lb, M, fmat_b, vet_line, nr_line);
    
    mat_c = alocar_matriz(N, M);
	zerar_matriz(mat_c, N, M);

    mat_c_thread = alocar_matriz(N, M);
	zerar_matriz(mat_c_thread, N, M);

    mat_c_bloco = alocar_matriz(N, M);
    zerar_matriz(mat_c_bloco, N, M);

    mat_c_bloco_thread = alocar_matriz(N, M);
    zerar_matriz(mat_c_bloco_thread, N, M);
	if ((mat_b == NULL) || (mat_a == NULL) || (mat_c == NULL) || (mat_c_thread == NULL) || (mat_c_bloco == NULL) || (mat_c_bloco_thread == NULL)) {
		printf("ERROR: Out of memory\n");
        exit(1);
	}
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação Sequencial
    printf("Inicio Multiplicação Sequencial.... Execuções: ");
    for(nCnt=0;nCnt<nLimit;nCnt++){
        printf("%d ", nCnt);
        fflush(stdout);
        zerar_matriz(mat_c, N, M);

        nStartTime = wtime();

        multiplicarIKJ(mat_a,mat_b,mat_c, N, La, M, Lb);
        nEndTime = wtime();

        nTimeIKJ += ( nEndTime - nStartTime );
    }
    printf("\n");
    fmat_c= fopen("multiIKJ.map-result","w");
	fileout_matriz(mat_c, N, M, fmat_c);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação Sequencial em Bloco
    printf("Inicio Multiplicação Sequencial em Bloco.... Execuções: ");
    for(nCnt=0;nCnt<nLimit;nCnt++){
        printf("%d ", nCnt);
        fflush(stdout);
        nStartTime = wtime();

        Vsubmat_a = particionar_matriz (mat_a, N, La, 1, nBlocos);
        Vsubmat_b = particionar_matriz (mat_b, Lb, M, 0, nBlocos);
        Vsubmat_c = constroi_submatrizv2 (N, M, nBlocos);

	    zerar_matriz(mat_c_bloco, N, M);
        for( nMulti = 0; nMulti < nBlocos; nMulti ++)
            multiplicar_submatriz (Vsubmat_a[nMulti], Vsubmat_b[nMulti], Vsubmat_c[nMulti]);
        
        for( nMulti = 0; nMulti < nBlocos; nMulti ++)
            somarIJ(mat_c_bloco,Vsubmat_c[nMulti]->matriz,mat_c_bloco, N, N, N, N);

        // LIBERAR MEMÓRIA
        Vsubmat_a = liberar_submatriz (Vsubmat_a, nBlocos);
        Vsubmat_b = liberar_submatriz (Vsubmat_b, nBlocos);
        Vsubmat_c= liberar_submatriz (Vsubmat_c, nBlocos);
        
        nEndTime = wtime();

        nTimeBloco += ( nEndTime - nStartTime );

    }
    printf("\n");
    fmat_c= fopen("multiBloco.map-result","w");
	fileout_matriz(mat_c_bloco, N, M, fmat_c);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação MultiThread
    printf("Inicio Multiplicação MultiThread.... Execuções: ");
    for(nCnt=0;nCnt<nLimit;nCnt++){
        printf("%d ", nCnt);
        fflush(stdout);
        zerar_matriz(mat_c_thread, N, M);
        nStartTime = wtime();

        for (int i = 0; i < nMaxThread; i++)
        {
            args[i].tid = i;
            args[i].ntasks = nMaxThread;
            pthread_create(&threads[i], NULL, execMultThread, (void *) (args+i));
        }
        for (int i = 0; i < nMaxThread; i++)
        {
            pthread_join(threads[i], NULL);
        }
        nEndTime = wtime();

        nTimeIKJThread += ( nEndTime - nStartTime );
    }
    printf("\n");
    fmat_c= fopen("multiIKJThread.map-result","w");
	fileout_matriz(mat_c_thread, N, M, fmat_c);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação MultiThread em Bloco
    printf("Inicio Multiplicação MultiThread em Bloco.... Execuções: ");
    for(nCnt=0;nCnt<nLimit;nCnt++){
        printf("%d ", nCnt);
        fflush(stdout);
        nStartTime = wtime();

        Vsubmat_a = particionar_matriz (mat_a, N, La, 1, nBlocos);
        Vsubmat_b = particionar_matriz (mat_b, Lb, M, 0, nBlocos);
        Vsubmat_c = constroi_submatrizv2 (N, M, nBlocos);

	    zerar_matriz(mat_c_bloco_thread, N, M);
        nMulti = 0;
        while (nMulti < nBlocos){
            for (int i = 0; i < nMaxThread; i++){
                if (nMulti < nBlocos){
                    args[i].tid = nMulti;
                    args[i].ntasks = nMaxThread;
                    pthread_create(&threads[i], NULL, execMultBlocoThread, (void *) (args+i));
                    nJoin++;
                }
                nMulti++;
            }
            for (int i = 0; i < nJoin; i++)
            {
                pthread_join(threads[i], NULL);
            }
            nJoin=0;
        }

        for( nMulti = 0; nMulti < nBlocos; nMulti ++)
            somarIJ(mat_c_bloco_thread,Vsubmat_c[nMulti]->matriz,mat_c_bloco_thread, N, N, N, N);

        // LIBERAR MEMÓRIA
        Vsubmat_a = liberar_submatriz (Vsubmat_a, nBlocos);
        Vsubmat_b = liberar_submatriz (Vsubmat_b, nBlocos);
        Vsubmat_c= liberar_submatriz (Vsubmat_c, nBlocos);
        
        nEndTime = wtime();

        nTimeBlocoThread += ( nEndTime - nStartTime );

    }
    printf("\n");
    fmat_c= fopen("multiBlocoThread.map-result","w");
	fileout_matriz(mat_c_bloco_thread, N, M, fmat_c);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    printf("\n\n");
    // Comparar resultados e tempos
    printf("\tCompara Matriz Sequencial x Matriz Bloco\n");
    comparar_matriz(mat_c,mat_c_bloco,N,M);
    printf("\n");
    printf("\tCompara Matriz Sequencial x Matriz Sequencial Thread\n");
    comparar_matriz(mat_c,mat_c_thread,N,M);
    printf("\n");
    printf("\tCompara Matriz Bloco x Matriz Bloco Thread\n");
    comparar_matriz(mat_c_bloco,mat_c_bloco_thread,N,M);
    printf("\n");

    nMidIKJ = nTimeIKJ/nLimit;
    printf("\tTempo Médio Multiplicação IKJ: %f\n", nMidIKJ);
    nMidIKJThread = nTimeIKJThread/nLimit;
    printf("\tTempo Médio Multiplicação IKJ Thread: %f\n", nMidIKJThread);

    printf("\n");

    nMidBloco = nTimeBloco/nLimit;
    printf("\tTempo Médio Multiplicação Bloco: %f\n", nMidBloco);
    nMidBlocoThread = nTimeBlocoThread/nLimit;
    printf("\tTempo Médio Multiplicação Bloco Thread: %f\n", nMidBlocoThread);

    printf("\n");
    printf("\tSpeedUp IKJ: %f\n", nMidIKJ/nMidIKJThread);
    printf("\tSpeedUp Bloco: %f\n", nMidBloco/nMidBlocoThread);

	liberar_matriz(mat_a,N,La);
	liberar_matriz(mat_b,Lb,M);
	liberar_matriz(mat_c,N,M);
    liberar_matriz(mat_c_thread,N,M);
	liberar_matriz(mat_c_bloco,N,M);
    liberar_matriz(mat_c_bloco_thread,N,M);

	fclose(fmat_a);
	fclose(fmat_b);
	fclose(fmat_c);
}
