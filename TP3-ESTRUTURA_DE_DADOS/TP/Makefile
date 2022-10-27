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
OBJS = $(OBJ)/main.o $(OBJ)/caixa_de_entrada.o $(OBJ)/servidor.o $(OBJ)/memlog.o $(OBJ)/email.o
HDRS = $(INC)/servidor.h $(INC)/caixa_de_entrada.h $(INC)/memlog.h $(INC)/email.h $(INC)/msgassert.h
CFLAGS = -g -Wall -c -I$(INC)
ANALISAMEM = ../analisamem/bin/analisamem
ENTRADA = entrada.txt
SAIDA = saida.txt

EXE = $(BIN)/tp3

all: comp

mem: $(EXE)
	$(EXE) -p ./out/memlog.out -l -I $(ENTRADA) -O $(SAIDA)
	$(ANALISAMEM) -i ./out/memlog.out -p ./out/mem

perf: $(EXE)
	$(EXE) -p ./out/perf.out -I $(ENTRADA) -O $(SAIDA)

gprof: $(EXE)
	$(EXE) -p ./out/gprof.out -i $(ENTRADA) -o $(SAIDA)
	gprof $(EXE) gmon.out  > ./out/gprof.txt

comp: $(EXE)

$(EXE): $(OBJS)
	$(CC) -pg -g -o $(BIN)/tp3 $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/servidor.o: $(HDRS) $(SRC)/servidor.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/servidor.o $(SRC)/servidor.cpp

$(OBJ)/email.o: $(HDRS) $(SRC)/email.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/email.o $(SRC)/email.cpp

$(OBJ)/caixa_de_entrada.o: $(HDRS) $(SRC)/caixa_de_entrada.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/caixa_de_entrada.o $(SRC)/caixa_de_entrada.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

clean:
	rm -f $(EXE) $(OBJS) gmon.out
