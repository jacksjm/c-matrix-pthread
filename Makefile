# GNU Makefile

CC = gcc
CCFLAGS = -Wall -O3 #-g -llikwid #-funroll-all-loops
LDFLAGS =
TARGET = main_matriz gera_matriz2 simple_matriz help
EXE = ./gera_matriz2
LINHA=10
COLUNA=10
EXPMAT=

all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

main_matriz: main_matriz.c matriz.o toolsv2.o matriz-operacoes.o
	$(CC) $(CCFLAGS) matriz-operacoes.o matriz.o toolsv2.o main_matriz.c -o $@ $(LDFLAGS)

gera_matriz2: matriz.o toolsv2.o gera_matriz2.c
	$(CC) $(CCFLAGS) matriz.o toolsv2.o gera_matriz2.c -o $@ $(LDFLAGS)

simple_matriz: simple_matriz.c matriz.o toolsv2.o
	$(CC) $(CCFLAGS) matriz.o toolsv2.o simple_matriz.c -o $@ $(LDFLAGS)

exe:
	$(EXE) $(LINHA) $(COLUNA) $(EXPMAT)

help:
	@echo
	@echo
	@echo "####### Exemplo de Execução #######"
	@echo "./gera_matriz2 10 10"
	@echo "./main_matriz 10x10-mat-1.map 10x10-mat-2.map"

clean:
	rm -f *.o *~ $(TARGET) *.map *.map-result
