# OPERAÇÕES DE MATRIZES 
Criação de uma biblioteca para operações com matrizes e operações com matrizes em bloco.

# BIBLIOTECA DE MATRIZES 
Utiliza-se uma biblioteca para manipulação de matrizes (`matric.h`).

# PASSOS PARA INICIALIZAÇÃO E COMPILAÇÃO
1. Realize a extração dos arquivos Matriz.zip em um diretório de sua escolha.
2. Localize o diretório através do Terminal (comando cd)
3. Ao acessar o diretório, execute o comando make (ex.: `~/Documentos/C/PPA$ make`) para compilar os arquivos. Será exibido no terminal algo semelhante a:
```
user@machine:~/Documentos/C/GitHub/c-matrix$ make
gcc -Wall -O3  -c matriz.c
gcc -Wall -O3  -c toolsv2.c
gcc -Wall -O3  -c matriz-operacoes.c
gcc -Wall -O3  matriz-operacoes.o matriz.o toolsv2.o main_matriz.c -o main_matriz 
gcc -Wall -O3  matriz.o toolsv2.o gera_matriz2.c -o gera_matriz2 
gcc -Wall -O3  matriz.o toolsv2.o simple_matriz.c -o simple_matriz 


####### Exemplo de Execução #######
./gera_matriz2 10 10
./main_matriz 10x10-mat-1.map 10x10-mat-2.map
```
4. Caso seja necessária uma recompilação, é aconselhavel a utilização do comando `make clean` antes da execução de um novo camando `make`, para que os arquivos executáveis sejam excluídos. (ex.: `~/Documentos/C/PPA$ make clean`)

# PASSOS PARA GERAÇÃO
1. Para gerar um arquivo, é necessário executar o comando gera_matriz2, passando os parâmetros de linha e coluna. (ex.: `./gera_matriz2 10 10`: Gera um arquivo com uma matriz 10x10 nomeado _10x10-mat.map_)

# PASSOS PARA EXECUÇÃO
1. Para a execução do arquivo main, é necessário executar o camando main_matriz, passandos os parâmetros de 'matriz a' e 'matriz b', que devem indicar o nome dos arquivos. (ex.: `./main_matriz 10x10-mat.map 10x10-mat.map`)

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
* `simple_matriz`: Função de execução simples, avalia os items da biblioteca com uma matriz simples de 10 x 10.

# OBSERVAÇÕES
* A função `gera_matriz2` gera um arquivo de nome fixo. Caso seja necessária a geração de dois arquivos, deverão ser ajustados manualmente o nome desses arquivos.
* Devido as tratativas realizadas de validação de Alocação de Matriz e de Compatibilidade de Matrizes, tanto o arquivo `main_matriz.c` quando a biblioteca `matriz-operacoes.c` foram ajustados (em específicos os parâmetros a serem passados). Com isso, caso seja necessário a alteração do programa `main_matriz.c` é importante se atentar aos parâmetros e posições dos mesmos.

# EXEMPLO DE EXECUÇÃO
```
user@machine:~/Documentos/C/GitHub/c-matrix$ ./main_matriz 10x10-mat.map 10x10-mat.map 

 ##### Multiplicação de Matrizes (IJK) #####
	Runtime: 0.000004
 ##### Multiplicação de Matrizes (blocov2) #####
	Runtime: 0.000059

VERIFICADO: Matrizes identicas
Runtime: 0.000001
Resultados individuais encontram-se nos arquivos <out*.map-result>.
```