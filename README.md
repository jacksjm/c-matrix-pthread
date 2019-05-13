# OPERAÇÕES DE MATRIZES 
Criação de uma biblioteca para operações com matrizes e operações com matrizes em bloco, ambas com e sem threads.

# BIBLIOTECA DE MATRIZES 
Utiliza-se uma biblioteca para manipulação de matrizes (`matriz.h`).

# PASSOS PARA INICIALIZAÇÃO E COMPILAÇÃO
1. Realize a extração dos arquivos MatrizThread.zip em um diretório de sua escolha.
2. Localize o diretório através do Terminal (comando cd)
3. Ao acessar o diretório, execute o comando make (ex.: `~/Documentos/C/MatrizThread$ make`) para compilar os arquivos. Será exibido no terminal algo semelhante a:
```
user@machine:~/Documentos/C/GitHub/c-matrix-pthread$ make
gcc -Wall -O3  -c matriz.c
gcc -Wall -O3  -c toolsv2.c
gcc -Wall -O3  -c matriz-operacoes-threads.c
gcc -Wall -O3  matriz-operacoes-threads.o matriz.o toolsv2.o main_matriz_thread.c -o main_matriz_thread -pthread
gcc -Wall -O3  matriz.o toolsv2.o gera_matriz2.c -o gera_matriz2 -pthread


####### Exemplo de Execução #######
./gera_matriz2 10 10
./main_matriz_thread 100x100-mat.map 100x100-mat.map 2
```
4. Caso seja necessária uma recompilação, é aconselhavel a utilização do comando `make clean` antes da execução de um novo camando `make`, para que os arquivos executáveis sejam excluídos. (ex.: `~/Documentos/C/MatrizThread$ make clean`)

# PASSOS PARA GERAÇÃO
1. Para gerar um arquivo, é necessário executar o comando gera_matriz2, passando os parâmetros de linha e coluna. (ex.: `./gera_matriz2 100 100`: Gera um arquivo com uma matriz 10x10 nomeado _10x10-mat.map_)

# PASSOS PARA EXECUÇÃO
1. Para a execução do arquivo main, é necessário executar o camando main_matriz, passandos os parâmetros de 'matriz a' e 'matriz b', que devem indicar o nome dos arquivos. (ex.: `./main_matriz_thread 100x100-mat.map 100x100-mat.map 2`)

# DESCRIÇÃO DAS FUNÇÕES
* `gera_matriz2`: Função responsável por gerar os arquivos .map a serem lidos pela main.
    | Parâmetros  | Descrição     |
    |-|-|
    |linhas|Número de Linhas|
    |colunas|Número de Colunas|
* `main_matriz`: Função principal, responsável por executar as operações.
    | Parâmetros  | Descrição     |
    |-|-|
    |matrizA|Matriz A que será utilizada para as operações|
    |matrizB|Matriz B que será utilizada para as operações|
    |thread|Número de Threads a ser executado|

# OBSERVAÇÕES
* A função `gera_matriz2` gera um arquivo de nome fixo. Caso seja necessária a geração de dois arquivos, deverão ser ajustados manualmente o nome desses arquivos.
* Devido as tratativas realizadas de validação de Alocação de Matriz e de Compatibilidade de Matrizes, tanto o arquivo `main_matriz.c` quando a biblioteca `matriz-operacoes.c` foram ajustados (em específicos os parâmetros a serem passados). Com isso, caso seja necessário a alteração do programa `main_matriz.c` é importante se atentar aos parâmetros e posições dos mesmos.

# EXEMPLO DE EXECUÇÃO
```
user@machine:~/Documentos/C/GitHub/c-matrix-pthread$ ./main_matriz_thread 100x100-mat.map 100x100-mat.map 2
Inicio Multiplicação Sequencial.... Execuções: 0 1 2 3 4 5 6 7 8 9 
Inicio Multiplicação Sequencial em Bloco.... Execuções: 0 1 2 3 4 5 6 7 8 9 
Inicio Multiplicação MultiThread.... Execuções: 0 1 2 3 4 5 6 7 8 9 
Inicio Multiplicação MultiThread em Bloco.... Execuções: 0 1 2 3 4 5 6 7 8 9 


	Compara Matriz Sequencial x Matriz Bloco
VERIFICADO: Matrizes identicas
Runtime: 0.000018

	Compara Matriz Sequencial x Matriz Sequencial Thread
VERIFICADO: Matrizes identicas
Runtime: 0.000015

	Compara Matriz Bloco x Matriz Bloco Thread
VERIFICADO: Matrizes identicas
Runtime: 0.000011

	Tempo Médio Multiplicação IKJ: 0.000620
	Tempo Médio Multiplicação IKJ Thread: 0.000462

	Tempo Médio Multiplicação Bloco: 0.001291
	Tempo Médio Multiplicação Bloco Thread: 0.001887

	SpeedUp IKJ: 1.343087
	SpeedUp Bloco: 0.684032

```