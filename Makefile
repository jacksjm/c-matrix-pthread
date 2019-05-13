# GNU Makefile

CC = gcc
CCFLAGS = -Wall -O3 #-g -llikwid #-funroll-all-loops
LDFLAGS = -pthread
TARGET = main_matriz_thread gera_matriz2 help
EXE = ./gera_matriz2
LINHA=10
COLUNA=10
EXPMAT=

all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

main_matriz_thread: main_matriz_thread.c matriz.o toolsv2.o matriz-operacoes-threads.o
	$(CC) $(CCFLAGS) matriz-operacoes-threads.o matriz.o toolsv2.o main_matriz_thread.c -o $@ $(LDFLAGS)

gera_matriz2: matriz.o toolsv2.o gera_matriz2.c
	$(CC) $(CCFLAGS) matriz.o toolsv2.o gera_matriz2.c -o $@ $(LDFLAGS)

exe:
	$(EXE) $(LINHA) $(COLUNA) $(EXPMAT)

help:
	@echo
	@echo
	@echo "####### Exemplo de Execução #######"
	@echo "./gera_matriz2 100 100"
	@echo "./main_matriz_thread 100x100-mat.map 100x100-mat.map 2"

clean:
	rm -f *.o *~ $(TARGET) *.map *.map-result
