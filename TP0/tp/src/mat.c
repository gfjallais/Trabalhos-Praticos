//---------------------------------------------------------------------
// Arquivo	: mat.c
// Conteudo	: implementacao do TAD MAT 
// Autor	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico	: 2021-10-18 - arquivo criado
//		: 2021-10-21 - estrutura de diretorios
//              : 2021-11-14 - adequacao para versao 1.1 memlog
//                         : 2022-04-29 - substituicao de matriz estatica por dinamicamente alocada        
//---------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// Macro que realiza swap sem variavel auxiliar
#define ELEMSWAP(x,y) (x+=y,y=x-y,x-=y)

void criaMatriz(mat_tipo * mat, int tx, int ty, int id)
// Descricao: cria matriz com dimensoes tx X ty
// Entrada: mat, tx, ty, id
// Saida: mat
{
  int i;

  // verifica se os valores de tx e ty são validos
  erroAssert(tx>0,"Dimensao nula");
  erroAssert(ty>0,"Dimensao nula");

  // inicializa o identificador da matriz, para rastreamento
  mat->id = id;
  // inicializa as dimensoes da matriz
  mat->tamx = tx;
  mat->tamy = ty;
  // aloca memoria para a matriz
  mat->m = (double**) malloc(tx*sizeof(double*));
  erroAssert(mat->m != NULL, "Alocacao ma sucedida");

  for(i=0; i<tx; i++){

    mat->m[i] = (double*) malloc(ty*sizeof(double));

    erroAssert(mat->m[i] != NULL, "Alocacao ma sucedida");
    ESCREVEMEMLOG((long int)(&(mat->m[i])),sizeof(double*),mat->id);
  } 

}

double acessaMatriz(mat_tipo * mat)
// Descricao: acessa mat para fins de registro de acesso 
// Entrada: mat 
// Saida: mat
{
  int i, j;
  double aux, s=0.0;

  for (i=0; i<mat->tamx; i++){

    for(j=0; j<mat->tamy; j++){

      aux = mat->m[i][j];
      s+=aux;

      LEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);

    }

  }
  return s; // apenas para evitar que acesso seja eliminado
}

void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c)
// Descricao: soma as matrizes a e b e armazena o resultado em c
// Entrada: a, b
// Saida: c
{
  int i,j;

  // verifica se as dimensoes das matrizes a e b sao as mesmas
  erroAssert(a->tamx==b->tamx,"Dimensoes incompativeis");
  erroAssert(a->tamy==b->tamy,"Dimensoes incompativeis");

  // verifica se o arquivo de saída é válido
  erroAssert(c!=NULL, "Matriz de saída vazia");

  // faz a soma elemento a elemento
  for (i=0; i<a->tamx; i++){

    for(j=0; j<a->tamy; j++){

      c->m[i][j] = a->m[i][j] + b->m[i][j];

      LEMEMLOG((long int)(&(a->m[i][j])),sizeof(double),a->id);
      LEMEMLOG((long int)(&(b->m[i][j])),sizeof(double),b->id);
      ESCREVEMEMLOG((long int)(&(c->m[i][j])),sizeof(double),c->id);

    }

  }
}

void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c)
// Descricao: multiplica as matrizes a e b e armazena o resultado em c
// Entrada: a,b
// Saida: c
{
  int i,j,k;

  // verifica a compatibilidade das dimensoes 
  erroAssert(a->tamy==b->tamx,"Dimensoes incompativeis");

  // verifica se o arquivo de saída é válido
  erroAssert(c!=NULL, "Matriz de saída vazia");
  erroAssert((a->tamx == c->tamx && b->tamy == c->tamy),"Dimensoes incompativeis");

  
  // realiza a multiplicacao de matrizes
  for (i=0; i<c->tamx;i++){

    for (j=0; j<c->tamy;j++){

      for (k=0; k<a->tamy;k++){

        c->m[i][j] += a->m[i][k]*b->m[k][j];

        LEMEMLOG((long int)(&(a->m[i][k])),sizeof(double),a->id);
        LEMEMLOG((long int)(&(b->m[k][j])),sizeof(double),b->id);
        ESCREVEMEMLOG((long int)(&(c->m[i][j])),sizeof(double),c->id);

      }

    }

  }
}

void transpoeMatriz(mat_tipo *a)
// Descricao: transpoe a matriz a
// Entrada: a
// Saida: a
{

  int i,j;
  int maxdim = (a->tamx>a->tamy ? a->tamx : a->tamy);

  if(maxdim != a->tamx){

    a->m = realloc(a, sizeof(double*) * maxdim);

    erroAssert(a->m != NULL, "Alocacao ma sucedida");
  }

  if(maxdim != a->tamy){

    for(int i = 0; i < maxdim; i++){

      a->m[i] = realloc(a->m[i],sizeof(double) * maxdim);

      erroAssert(a->m[i] != NULL, "Alocacao ma sucedida");
    }

  }

  // faz a transposicao
  for (i=0; i<maxdim; i++){

    for(j=i+1; j<maxdim; j++){

      ELEMSWAP((a->m[i][j]),(a->m[j][i]));

      ESCREVEMEMLOG((long int)(&(a->m[i][j])),sizeof(double),a->id);
      ESCREVEMEMLOG((long int)(&(a->m[j][i])),sizeof(double),a->id);
    }

  }

  if(a->tamx < maxdim){

    for(int i=0; i < maxdim ;i++){

      a->m[i] = realloc(a->m[i],sizeof(double) * a->tamx);

      erroAssert(a->m[i] != NULL, "Alocacao ma sucedida");
      ESCREVEMEMLOG((long int)(&(a->m[i])),sizeof(double*),a->id);
    }

  }

  if(a->tamy < maxdim){

    a->m = realloc(a->m, sizeof(double*) * a->tamy);

    erroAssert(a->m != NULL, "Alocacao ma sucedida");
  }
  ELEMSWAP((a->tamx),(a->tamy));
}

void destroiMatriz(mat_tipo *a)
// Descricao: destroi a matriz a, que se torna inacessível
// Entrada: a
// Saida: a
{
  int i;
  // apenas um aviso se a matriz for destruida mais de uma vez
  avisoAssert(((a->tamx>0)&&(a->tamy>0)),"Matriz já foi destruida");
  
  // libera a memoria alocada dinamicamente
  for(i = 0; i < a->tamx; i++){
    free(a->m[i]);
  }
  free(a->m);
  // torna as dimensoes invalidas
  a->id = a->tamx = a->tamy = -1;
}
