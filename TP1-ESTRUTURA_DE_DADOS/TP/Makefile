#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: Macros para compilação, análise de memoria e execução do programa jogo.cpp
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
OBJS = $(OBJ)/carta.o $(OBJ)/jogador.o $(OBJ)/jogo.o $(OBJ)/rodada.o $(OBJ)/lista.o
HDRS = $(INC)/carta.h $(INC)/jogador.h $(INC)/rodada.h $(INC)/lista.h
CFLAGS = -Wall -c -I$(INC)
ANALISAMEM = ../analisamem/bin/analisamem
ENTRADA = entrada.txt

EXE = $(BIN)/tp1

all: comp perf

mem: $(EXE)
	$(EXE) -p ./out/memlog.out -l -1 $(ENTRADA)
	$(ANALISAMEM) -i ./out/memlog.out -p ./out/mem

perf: $(EXE)
	$(EXE) -p ./out/perf.out -1 $(ENTRADA)

gprof: $(EXE)
	$(EXE) -p ./out/gprof.out -1 $(ENTRADA)
	gprof $(EXE) gmon.out  > ./out/gprof.txt

comp: $(EXE)

$(EXE): $(OBJS)
	$(CC) -pg -g -o $(BIN)/tp1 $(OBJS) $(LIBS)

$(OBJ)/jogo.o: $(HDRS) $(SRC)/jogo.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/jogo.o -c $(SRC)/jogo.cpp 

$(OBJ)/jogador.o: $(HDRS) $(SRC)/jogador.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/jogador.o -c $(SRC)/jogador.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

$(OBJ)/carta.o: $(HDRS) $(SRC)/carta.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/carta.o -c $(SRC)/carta.cpp 

$(OBJ)/lista.o: $(HDRS) $(SRC)/lista.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/lista.o $(SRC)/lista.cpp

$(OBJ)/rodada.o: $(HDRS) $(SRC)/rodada.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/rodada.o -c $(SRC)/rodada.cpp 

clean:
	rm -f $(EXE) $(OBJS) gmon.out
