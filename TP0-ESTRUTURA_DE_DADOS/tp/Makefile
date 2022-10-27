#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: Macros para compilação do programa matop.c e para a análise computacional e de memória desse.
# Autor		: Gabriel Franco Jallais. (gabrieljallais@dcc.ufmg.br)
# Histórico	: 2022-05-01 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera os histogramas e gráficos de distância de pilha, e arquivos para ánalise de localidade de memória
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#				: make comp - apenas compila os arquivos, gerando os arquivos .o e o executável 
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)
ARQMEM = ../teste/teste5.txt
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/matop

all:  mem perf gprof comp

mem: $(EXE)

	$(EXE) -s -p /tmp/somalog.out -l -1 $(ARQMEM) -2 $(ARQMEM) -o /tmp/somamat5.txt 
	rm -rf /tmp/somamat
	mkdir /tmp/somamat
	$(ANALISAMEM) -i /tmp/somalog.out -p /tmp/somamat/somamat

	$(EXE) -m -p /tmp/multlog.out -l -1 $(ARQMEM) -2 $(ARQMEM) -o /tmp/multmat5.txt 
	rm -rf /tmp/multmat
	mkdir /tmp/multmat
	$(ANALISAMEM) -i /tmp/multlog.out -p /tmp/multmat/multmat
	
	$(EXE) -t -p /tmp/transplog.out -l -1 $(ARQMEM) -o /tmp/transpmat5.txt  
	rm -rf /tmp/transpmat
	mkdir /tmp/transpmat
	$(ANALISAMEM) -i /tmp/transplog.out -p /tmp/transpmat/transpmat

perf: $(EXE)
	$(EXE) -s -p /tmp/somamat500.out  -1 ../teste/teste500.txt -2 ../teste/teste500.txt 
	$(EXE) -m -p /tmp/multmat500.out  -1 ../teste/teste500.txt -2 ../teste/teste500.txt 
	$(EXE) -t -p /tmp/transpmat500.out  -1 ../teste/teste500.txt -2 ../teste/teste500.txt 
	$(EXE) -s -p /tmp/somamat400.out  -1 ../teste/teste400.txt -2 ../teste/teste400.txt
	$(EXE) -m -p /tmp/multmat400.out  -1 ../teste/teste400.txt -2 ../teste/teste400.txt
	$(EXE) -t -p /tmp/transpmat400.out  -1 ../teste/teste400.txt -2 ../teste/teste400.txt
	$(EXE) -s -p /tmp/somamat300.out  -1 ../teste/teste300.txt -2 ../teste/teste300.txt 
	$(EXE) -m -p /tmp/multmat300.out  -1 ../teste/teste300.txt -2 ../teste/teste300.txt 
	$(EXE) -t -p /tmp/transpmat300.out  -1 ../teste/teste300.txt -2 ../teste/teste300.txt
	$(EXE) -s -p /tmp/somamat200.out  -1 ../teste/teste200.txt -2 ../teste/teste200.txt 
	$(EXE) -m -p /tmp/multmat200.out  -1 ../teste/teste200.txt -2 ../teste/teste200.txt 
	$(EXE) -t -p /tmp/transpmat200.out  -1 ../teste/teste200.txt -2 ../teste/teste200.txt 
	$(EXE) -s -p /tmp/somamat100.out  -1 ../teste/teste100.txt -2 ../teste/teste100.txt
	$(EXE) -m -p /tmp/multmat100.out  -1 ../teste/teste100.txt -2 ../teste/teste100.txt
	$(EXE) -t -p /tmp/transpmat100.out  -1 ../teste/teste100.txt -2 ../teste/teste100.txt 

gprof: $(EXE)
	$(EXE) -s -p /tmp/somamat2000gprof.out  -1 ../teste/teste2000.txt -2 ../teste/teste2000.txt
	gprof $(EXE) gmon.out > /tmp/somamat2000gprof.txt
	$(EXE) -m -p /tmp/multmat2000gprof.out  -1 ../teste/teste2000.txt -2 ../teste/teste2000.txt 
	gprof $(EXE) gmon.out > /tmp/multmat2000gprof.txt
	$(EXE) -t -p /tmp/transpmat2000gprof.out  -1 ../teste/teste2000.txt -2 ../teste/teste2000.txt
	gprof $(EXE) gmon.out > /tmp/transpmat2000gprof.txt

	$(EXE) -s -p /tmp/somamat1000gprof.out  -1 ../teste/teste1000.txt -2 ../teste/teste1000.txt
	gprof $(EXE) gmon.out > /tmp/somamat1000gprof.txt
	$(EXE) -m -p /tmp/multmat1000gprof.out  -1 ../teste/teste1000.txt -2 ../teste/teste1000.txt
	gprof $(EXE) gmon.out > /tmp/multmat1000gprof.txt
	$(EXE) -t -p /tmp/transpmat1000gprof.out  -1 ../teste/teste1000.txt -2 ../teste/teste1000.txt
	gprof $(EXE) gmon.out > /tmp/transpmat1000gprof.txt

comp: $(EXE)

$(EXE): $(OBJS)
	$(CC) -pg -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c 

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 

clean:
	rm -f $(EXE) $(OBJS) gmon.out
