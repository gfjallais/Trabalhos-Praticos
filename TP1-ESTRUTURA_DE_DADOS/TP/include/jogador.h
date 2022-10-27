#ifndef JOGADOR_H
#define JOGADOR_H
#include <sstream>
#include "carta.h"
#include "lista.h"

//Define a classe jogador, para representar cada jogador da partida

class jogador{
    public:
        jogador();
        jogador(std::string nome, int dinheiro_inicial, carta *mao);
        int get_montante();
        void alt_montante(int n);
        std::string get_nome();
        void set_vencedor(bool b);
        bool eh_vencedor();
        void define_mao();
        void set_aposta(int aposta);
        int get_aposta();
        bool operator==(jogador j);
        int get_categoria_jogada();
        void set_mao(carta *mao);
        
    protected:
        carta v_mao[5]; //mao do jogador
        lista l_mao; //mao em lista para auxiliar na definicao da mao
        bool msm_naipe; //diz se todas as cartas da mao possuem o mesmo naipe
        std::string _nome;
        int montante;
        int jogada[4]; //vetor com valores sobre a mao do jogador, classificacao, carta mais alta, e critérios de desempate
        bool vencedor;
        int num_vitorias;
        int aposta;
    friend class rodada;
};

#endif