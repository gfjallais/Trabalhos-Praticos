//---------------------------------------------------------------------
// Arquivo      : matop.c
// Conteudo     : programa de avaliacao do TAD MAT 
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br), Gabriel Franco Jallais (gabriel@dcc.ufmg.br)
// Historico    : 2021-10-18 - arquivo criado
//              : 2021-10-21 - estrutura de diretorios
//              : 2021-10-25 - opcoes de linha de comando 
//              : 2021-11-14 - adequacao para versao 1.1 memlog 
//              : 2022-04-30 - adequacao para os requisitos do TP0
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include "mat.h"
#include "memlog.h" 
#include "msgassert.h" 

// definicoes de operacoes a serem testadas
#define OPSOMAR 1
#define OPMULTIPLICAR 2
#define OPTRANSPOR 3

// variaveis globais para opcoes
static int opescolhida;
char lognome[100];
int optx, opty, regmem;
char arq1[100], arq2[100], arqout[100];

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr,"matop\n");
  fprintf(stderr,"\t-s \t(soma matrizes) \n");
  fprintf(stderr,"\t-m \t(multiplica matrizes) \n");
  fprintf(stderr,"\t-t \t(transpõe matriz 1)\n");
  fprintf(stderr,"\t-1 m1.txt\t(matriz 1)\n");
  fprintf(stderr,"\t-2 m2.txt\t(matriz 2)\n");
  fprintf(stderr,"\t-o res.out\t(matriz resultante)\n");
  fprintf(stderr,"\t-p log.out\t((registro de desempenho)\n");
  fprintf(stderr,"\t-l \t(padrão de acesso e localidade)\n");
}


void parseArgs(int argc,char ** argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, optx, opty, regmem, lognome
{
     // variaveis externas do getopt
     extern char * optarg;
     extern int optind;

     // variavel auxiliar
     int c;

     // inicializacao variaveis globais para opcoes
     opescolhida = -1;
     optx = -1;
     opty = -1;
     regmem = 0;
     lognome[0] = 0;
     arqout[0] = 0;

     // getopt - letra indica a opcao, : junto a letra indica parametro
     // no caso de escolher mais de uma operacao, vale a ultima
     while ((c = getopt(argc, argv, "smtp:x:y:1:2:o:l")) != EOF)
       switch(c) {
         case 'm':
		  avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = OPMULTIPLICAR;
                  break;
         case 's':
		  avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = OPSOMAR;
                  break;
         case 't':
		  avisoAssert(opescolhida==-1,"Mais de uma operacao escolhida");
	          opescolhida = OPTRANSPOR;
                  break;
         case 'p': 
	          strcpy(lognome,optarg);
		  break;
         case 'l': 
	          regmem = 1;
		  break;
         case '1':
            erroAssert(strlen(optarg)>0,
            "matop - nome de arquivo de etnrada tem que ser definido");
            strcpy(arq1,optarg);
            erroAssert(fopen(arq1, "r"),"matop - arquivo de teste 1 nao abriu corretamente");
      break;
         case '2':
            erroAssert(strlen(optarg)>0,
            "matop - nome de arquivo de etnrada tem que ser definido");
            strcpy(arq2,optarg);
            erroAssert(fopen(arq2, "r"),"matop - arquivo de teste 1 nao abriu corretamente");
      break;
         case 'o':
            erroAssert(strlen(optarg)>0,
            "matop - nome de arquivo de registro de acesso tem que ser definido");
            strcpy(arqout,optarg);
            erroAssert(fopen(arqout, "w"),"matop - arquivo de output nao abriu corretamente");
      break;
         default:
                  uso();
                  exit(1);

       }
       // verificacao da consistencia das opcoes
       erroAssert(opescolhida>0,"matop - necessario escolher operacao");
       erroAssert(strlen(lognome)>0,
         "matop - nome de arquivo de registro de acesso tem que ser definido");
}

void leMatriz(mat_tipo *a, char *arq, int id)
// Descricao: cria uma matriz a partir de um arquivo .txt
// Entrada: matriz* a, char* arq, int id
// Saida: nenhuma
{
    FILE *file = fopen(arq,"r");
    // garante que o arquivo foi aberto corretamente
    erroAssert(fopen(arq, "r"),"matop - arquivo de teste 1 nao abriu corretamente");

    if(file!=NULL){
      int tamx = 0, tamy = 0;

      // eh feita a leitura da matriz
      fscanf(file,"%d %d\n", &tamx, &tamy);
      erroAssert(tamx > 0, "Número de linhas inválido");
      erroAssert(tamy > 0, "Número de colunas inválido");
      criaMatriz(a, tamx, tamy, id);

      for(int i=0; i<a->tamx; i++){

          for(int j=0; j<tamy; j++){
              fscanf(file, "%lf", &a->m[i][j]);
              ESCREVEMEMLOG((long int)(&(a->m[i][j])),sizeof(double), a->id);
          }

          fscanf(file, "\n");

      }

      fclose(file);

    }
}

void geraOutput(mat_tipo *c, char *arq)
// Descricao: cria uma matriz de saída a partir do resultado das operacoes efetuadas
// Entrada: matriz* c, char* arq
// Saida: nenhuma
{
      FILE * out = fopen(arq,"w");
      // garante que o arquivo foi aberto corretamente
      erroAssert(fopen(arq, "w"),"matop - arquivo de output nao abriu corretamente");

      if(out!=NULL){

        // eh feita a escrita do resultado no arquivo
        fprintf(out, "%d %d\n", c->tamx, c->tamy);

        for(int i=0; i<c->tamx; i++){

          for(int j=0; j<c->tamy; j++){

            fprintf(out, "%8.2lf ", c->m[i][j]);

          }

          fprintf(out, "\n");

        }
        fclose(out);

      }

}


int main(int argc, char ** argv)
// Descricao: programa principal para execucao de operacoes de matrizes 
// Entrada: argc e argv
// Saida: depende da operacao escolhida
{
  // ate 3 matrizes sao utilizadas, dependendo da operacao
  mat_tipo a, b, c;

  // avaliar linha de comando
  parseArgs(argc,argv);

  // iniciar registro de acesso
  iniciaMemLog(lognome);

  // ativar ou nao o registro de acesso
  if (regmem){ 

    ativaMemLog();

  }

  else{

    desativaMemLog();

  }

  // execucao dependente da operacao escolhida
  switch (opescolhida){
    case OPSOMAR:
         // le matrizes a e b dos arquivos passados, que sao somadas para a matriz c
	      // matriz c é impressa no arquivo de saída e todas as matrizes sao destruidas
	 defineFaseMemLog(0);
         leMatriz(&a, arq1, 0);
         leMatriz(&b, arq2, 1);
         criaMatriz(&c,a.tamx,a.tamy,2);

	 defineFaseMemLog(1);

         acessaMatriz(&a);
         acessaMatriz(&b);
         acessaMatriz(&c);
         somaMatrizes(&a,&b,&c);

	 defineFaseMemLog(2);

         acessaMatriz(&c);

	 if (regmem) geraOutput(&a, arqout);

         destroiMatriz(&a);
         destroiMatriz(&b);
         destroiMatriz(&c);

	 break;
    case OPMULTIPLICAR:
         // le matrizes a e b dos arquivos passados, que sao multiplicadas para a matriz c
	       // matriz c é impressa no arquivo de saída e todas as matrizes sao destruidas
	 defineFaseMemLog(0);

         leMatriz(&a, arq1, 0);
         leMatriz(&b, arq2, 1);
         criaMatriz(&c,a.tamx,b.tamy,2);

	 defineFaseMemLog(1);

         acessaMatriz(&a);
         acessaMatriz(&b);
         acessaMatriz(&c);
         multiplicaMatrizes(&a,&b,&c);

	 defineFaseMemLog(2);

         acessaMatriz(&c);

	 if (regmem) geraOutput(&c, arqout);

         destroiMatriz(&a);
         destroiMatriz(&b);
         destroiMatriz(&c);
	 break;
    case OPTRANSPOR:
         // le matriz a passada como entrada, que e transposta, impressa no arquivo de saída e destruida
	 defineFaseMemLog(0);

         leMatriz(&a, arq1, 0);

	 defineFaseMemLog(1);

         acessaMatriz(&a);
	       transpoeMatriz(&a);

	 defineFaseMemLog(2);

         acessaMatriz(&a);

	 if (regmem) geraOutput(&a, arqout);

         destroiMatriz(&a);
	 break;
   default:
         // nao deve ser executado, pois ha um erroAssert em parseArgs
         uso();
	 exit(1);
  }

  // conclui registro de acesso
  return finalizaMemLog();
}

