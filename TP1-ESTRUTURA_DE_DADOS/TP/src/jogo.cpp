#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <getopt.h>
#include "memlog.cpp"
#include "../include/msgassert.h"
#include "../include/rodada.h"

std::string jogadas[11] = {"I", "RSF", "SF", "FK", "FH", "F", "S", \
 "TK", "TP", "OP", "HC"};

char lognome[100];
int regmem;
char arq1[100];

void parseArgs(int argc,char ** argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, optx, opty, regmem, lognome
{
    // variaveis externas do getopt
    extern char * optarg;

    // variavel auxiliar
    int c;

    // inicializacao variaveis globais para opcoes
    regmem = 0;
    lognome[0] = 0;
    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "p:1:l")) != EOF)
    switch(c) {
    case '1':
        erroAssert(strlen(optarg)>0, "nome de arquivo de etnrada tem que ser definido");
        strcpy(arq1,optarg);
        break;
    case 'p': 
        strcpy(lognome,optarg);
        break;
    case 'l': 
        regmem = 1;
        break;
        default:
        exit(1);

    }
    // verificacao da consistencia das opcoes
    erroAssert(strlen(lognome)>0,
        "matop - nome de arquivo de registro de acesso tem que ser definido");
}

void swap(jogador *xp, jogador *yp)
{
    jogador temp = *xp;
    *xp = *yp;
    *yp = temp;
}
//Ordena os jogadores com base nos seus respectivos montantes
void selectionSort_m (jogador arr[], int n)
{
    int i, j, min_mont;
 
    for (i = 0; i < n-1; i++){
        min_mont= i;
        for (j = i+1; j < n; j++){
            if (arr[j].get_montante() > arr[min_mont].get_montante()){
                min_mont = j;
            }     
        }
        swap(&arr[min_mont], &arr[i]);
    }
}
//Ordena os jogadores com base nos seus respectivos nomes
void selectionSort_n(jogador arr[], int n)
{
    int i, j, min_mont;
 
    for (i = 0; i < n-1; i++){
        min_mont= i;
        for (j = i+1; j < n; j++){
            if (arr[j].get_nome() < arr[min_mont].get_nome()){
                min_mont = j;
            }     
        }
        swap(&arr[min_mont], &arr[i]);
        LEMEMLOG((long int)(&arr[j]),sizeof(jogador),1);
    }
}

bool valida_entrada(std::string entrada){
    std::fstream input;
    input.open(entrada, std::ios::in);
    erroAssert(input.is_open(), "Arquivo entrada.txt nao abriu corretamente");
    bool is_valid;
    std::string line;
    std::string regex_pattern1 = "([0-9]+ [0-9]+)";
    std::string regex_pattern2 = "(?=[^0-9]).*(?=[ ][0-9]) ([0-9]{1,2}[PECO])";
    std::regex regex_rule1(regex_pattern1);
    std::regex regex_rule2(regex_pattern2);
    int num_rodadas, num_jogadores, lixo;

    getline(input, line);
    is_valid = std::regex_match(line, regex_rule1);
    erroAssert(is_valid, "Entrada invalida, primeira linha");
    sscanf(line.c_str(), "%d %d", &num_rodadas, &lixo);

    for(int i = 0; i < num_rodadas; i++){
        getline(input, line);
        is_valid = std::regex_match(line, regex_rule1);
        erroAssert(is_valid, "Entrada invalida, linha anterior aos nomes");
        sscanf(line.c_str(), "%d %d", &num_jogadores, &lixo);
        for(int j = 0; j < num_jogadores; j++){
            getline(input, line);
            is_valid = std::regex_match(line, regex_rule2);
            erroAssert(is_valid, "Entrada invalida, nomes");
        }
    }
    input.close();
    return is_valid;
}

int main(int argc, char *argv[]){
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
    defineFaseMemLog(0);

    std::fstream input, output;
    std::string line;
    int num_rodadas, dinheiro_inicial, num_jogadores, pingo, aposta;
    std::string nome_jogador, cartas[5];
    carta mao[5];
    
    //Abre os arquivos de etrada e saída, e checa se foi bem sucedido
    input.open(arq1);
    erroAssert(input.is_open(), "Arquivo entrada.txt nao abriu corretamente");
    
    output.open("./saida.txt", std::ios::out);
    erroAssert(output.is_open(), "Arquivo entrada.txt nao abriu corretamente");
    
    erroAssert(valida_entrada(arq1), "Entrada invalida");

    //Comeca a leitura da entrada
    getline(input, line);
    sscanf(line.c_str(), "%d %d", &num_rodadas, &dinheiro_inicial);

    rodada rodadas;
    //Le os blocos referentes a cada rodada
    for(int i = 0; i < num_rodadas; i++){
        jogador tmp;
        getline(input, line);
        sscanf(line.c_str(), "%d %d", &num_jogadores, &pingo);
        rodadas.set_valid(true);

        if(!(pingo >= 50)){
            rodadas.set_valid(false);
        }

        if(i == 0) rodadas.set_num_j_p(num_jogadores);

        if(rodadas.is_valid()){
            rodadas.set_num_j_r(num_jogadores);
            rodadas.set_pingo(pingo);
            //Le cada jogador
            for(int j = 0; j < num_jogadores; j++){
                getline(input, line);
                std::stringstream ss(line);
                
                ss >> nome_jogador >> aposta >> cartas[0] >> cartas[1] >> cartas[2] >> cartas[3] >> cartas[4];
                if(!(aposta > 0 && aposta%50 == 0)){
                    rodadas.set_valid(false);
                }   

                for(int k = 0; k < 5; k++){
                    mao[k] = carta(cartas[k]);
                    LEMEMLOG((long int)(&(mao[k])),sizeof(carta),1);
                }

                if(i == 0){
                    tmp = jogador(nome_jogador, dinheiro_inicial, mao);
                    tmp.set_aposta(aposta);
                    rodadas.jogadores_rodada[j] = tmp;
                }
                else{
                    for(int m = 0; m < rodadas.get_num_j_p(); m++){
                        if(nome_jogador.compare(rodadas.jogadores_rodada[m].get_nome()) == 0){
                            rodadas.jogadores_rodada[m].set_aposta(aposta);
                            rodadas.jogadores_rodada[m].set_mao(mao);
                            rodadas.jogadores_rodada[m].define_mao();
                            LEMEMLOG((long int)(&rodadas.jogadores_rodada[m]),sizeof(jogador),0);
                        }
                    }
                }
                LEMEMLOG((long int)(&rodadas.jogadores_rodada[j]),sizeof(jogador),0);
            }
            //Finaliza a rodada definindo vencedores e arrecadando o dinheiro para distribuir
            rodadas.def_vencedores();
            rodadas.arrecadar();

            if(rodadas.is_valid()){
                int aux = rodadas.get_pote();
                rodadas.distribuir_premiacao();

                for(int m = 0; m < rodadas.get_num_j_p(); m++){
                    if(rodadas.jogadores_rodada[m].eh_vencedor()){
                        output << rodadas.get_num_v() << " " << (aux)/(rodadas.get_num_v()) << " "
                        << jogadas[rodadas.jogadores_rodada[m].get_categoria_jogada()] << std::endl;
                        break;
                    }   
                }
                
                selectionSort_n(rodadas.jogadores_rodada, rodadas.get_num_j_p());
                for(int m = 0; m < rodadas.get_num_j_p(); m++){
                    if(rodadas.jogadores_rodada[m].eh_vencedor()){
                        output << rodadas.jogadores_rodada[m].get_nome() << std::endl;
                        LEMEMLOG((long int)(&rodadas.jogadores_rodada[m]),sizeof(jogador),0);
                    }
                }
            }
            for(int m = 0; m < rodadas.get_num_j_p(); m++){
                rodadas.jogadores_rodada[m].set_vencedor(false);
            }
            rodadas.set_num_v(0);
        }
        if(!rodadas.is_valid()){
            output << 0 << " " << 0 << " I" << std::endl;
        }
    }

    output << "####" << std::endl;
    selectionSort_m(rodadas.jogadores_rodada, rodadas.get_num_j_p());
    for(int i = 0; i < rodadas.get_num_j_p(); i++){
        output << rodadas.jogadores_rodada[i].get_nome() << " " << rodadas.jogadores_rodada[i].get_montante() << std::endl;
    }
    
    input.close();
    output.close();

    return finalizaMemLog();
}