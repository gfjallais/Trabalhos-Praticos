#include <iostream>
#include <string>
#include <fstream>
#include <getopt.h>
#include <cctype>
#include <sstream>
#include "memlog.cpp"
#include "list_template.h"
#include "process_string.h"
#include "quicksort.h"

char logname[100];
int regmem, median, part_max;
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
    while ((c = getopt(argc, argv, "p:i:I:o:O:m:M:s:S:l")) != EOF)
    switch(std::tolower(c)) {
        case 'i':
            erroAssert(strlen(optarg)>0, "nome de arquivo de etnrada tem que ser definido");
            strcpy(arqin,optarg);
            break;
        case 'o':
            erroAssert(strlen(optarg)>0, "nome de arquivo de saida tem que ser definido");
            strcpy(arqout,optarg);
            break;
        case 'm':
            erroAssert(atoi(optarg)>=0, "valor negativo de mediana");
            median = atoi(optarg);
            break;
        case 's':
            erroAssert(atoi(optarg)>=0, "valor negativo para o tamanho maximo de particao");
            part_max = atoi(optarg);
            break;
        case 'p':
            strcpy(logname,optarg);
            erroAssert(strlen(logname)>0, "main - nome de arquivo de registro de acesso tem que ser definido");
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

    //Abre os arquivos de etrada e saída, e checa se foi bem sucedido
    input.open(arqin);
    erroAssert(input.is_open(), "Arquivo de entrada nao abriu corretamente");
    
    output.open(arqout, std::ios::out);
    erroAssert(output.is_open(), "Arquivo de saida nao abriu corretamente");

    int read = 0;
    std::string word;
    list<std::string> list_of_words;
    int order[26] = {0};

    defineFaseMemLog(0);

    while(getline(input,line)){
        if(line == "#TEXTO"){
            while(getline(input, line)){
                if(line.back() == ' ') line.pop_back();
                std::stringstream ss(line);
                if(line == "#ORDEM") break;
                while(!ss.eof()){
                    ss >> word;
                    process_string(&word);
                    list_of_words.insert(word, true);
                    ESCREVEMEMLOG((long int)((list_of_words.at_position(list_of_words.get_size(), false))),sizeof(node<std::string>), 0);
                }
            }
            read++;
        }
        if(line == "#ORDEM"){
            getline(input,line);
            std::stringstream ss(line);
            char letter;
            for(int i = 0; i < 26; i++){
                ss >> letter;
                order[std::tolower(letter) - 97] = i + 97;
            }
            read++;
        }
        if(read == 2) break;
    }

    defineFaseMemLog(1);
    quicksort(&list_of_words, 0, list_of_words.get_size() - 1, median, part_max, order);

    defineFaseMemLog(2);
    for(int i = 0; i < list_of_words.get_size(); i++){
        output << list_of_words.at_position(i, false)->get_item() << " " << list_of_words.at_position(i, false)->get_quant() << std::endl;
        LEMEMLOG((long int)((list_of_words.at_position(i, false))),sizeof(node<std::string>), 0);
    }
    output << "#FIM" << std::endl;

    input.close();
    output.close();

    if(regmem){
        return finalizaMemLog();
    }
}