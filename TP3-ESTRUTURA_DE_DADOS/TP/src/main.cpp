#include <iostream>
#include <string>
#include <fstream>
#include <getopt.h>
#include <sstream>
#include <cstring>
#include "memlog.h"
#include "msgassert.h"
#include "servidor.h"

char logname[100];
int regmem;
char arqin[100], arqout[100];

void parseArgs(int argc,char ** argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: regmem, logname
{
    // variaveis externas do getopt
    extern char * optarg;

    // variavel auxiliar
    int c;

    // inicializacao variaveis globais para opcoes
    regmem = 0;
    logname[0] = 0;
    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "p:i:I:o:O:l")) != EOF)
    switch(std::tolower(c)) {
        case 'i':
            erroAssert(strlen(optarg)>0, "nome de arquivo de entrada tem que ser definido");
            strcpy(arqin,optarg);
            break;
        case 'o':
            erroAssert(strlen(optarg)>0, "nome de arquivo de saida tem que ser definido");
            strcpy(arqout,optarg);
            break;
        case 'p':
            erroAssert(strlen(optarg)>0, "main - nome de arquivo de registro de acesso tem que ser definido");
            strcpy(logname,optarg);
            break;
        case 'l':
            regmem = 1;
            break;
        default:
            exit(1);
    }
}

int main(int argc, char *argv[]){
    parseArgs(argc,argv);

    //iniciar registro de acesso
    if(strlen(logname)>0) iniciaMemLog(logname);

    // ativar ou nao o registro de acesso
    if (regmem){
        ativaMemLog();
    }

    else{
        desativaMemLog();
    }

    std::fstream input, output;
    std::string line;
    int m;

    //Abre os arquivos de etrada e saída, e checa se foi bem sucedido
    input.open(arqin);
    erroAssert(input.is_open(), "Arquivo de entrada nao abriu corretamente");

    getline(input, line);
    m = stoi(line);
    
    servidor serv(m, arqout);
    
    defineFaseMemLog(0);

    while(getline(input, line)){
        serv.processa_opcao(line);
    }

    input.close();

    defineFaseMemLog(3);
    for(int i = 0; i < m; i++){
        serv.tabela_hash[i].~caixa_de_entrada();
    }

    if(strlen(logname) > 0 || regmem){
        return finalizaMemLog();
    }
}