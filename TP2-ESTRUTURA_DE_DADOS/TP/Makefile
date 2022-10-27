#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: Macros para compilação, análise de memoria e execução do programa main.cpp
# Autor		: Gabriel Franco Jallais. (gabrieljallais@dcc.ufmg.br)
# Histórico	: 2022-06-02 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera os histogramas e gráficos de distância de pilha, e arquivos para ánalise de localidade de memória
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#				: make comp - apenas compila os arquivos, gerando os arquivos .o e o executável 
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o
HDRS = $(INC)/list_template.h $(INC)
CFLAGS = -g -Wall -c -I$(INC)
ANALISAMEM = ../analisamem/bin/analisamem
ENTRADA = teste.txt
SAIDA = out.txt

EXE = $(BIN)/tp2

all: comp perf

mem: $(EXE)
	$(EXE) -p /tmp/memlog.out -l -I $(ENTRADA) -O $(SAIDA) -m 5 -S 10
	$(ANALISAMEM) -i /tmp/memlog.out -p /tmp/mem

perf: $(EXE)
	$(EXE) -p /tmp/perf.out -I $(ENTRADA) -O $(SAIDA) -m 5 -S 10

gprof: $(EXE)
	$(EXE) -p /tmp/gprof.out -i $(ENTRADA) -o $(SAIDA) -M 5 -S 10
	gprof $(EXE) gmon.out  > /tmp/gprof.txt

comp: $(EXE)

$(EXE): $(OBJS)
	$(CC) -pg -g -o $(BIN)/tp2 $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

clean:
	rm -f $(EXE) $(OBJS) gmon.out
