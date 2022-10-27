#ifndef RODADA_H
#define RODADA_H
#include <iostream>
#include "jogador.h"

//Define a classe rodada, para representar cada rodada da partida

class rodada {
    public:
        rodada();
        void arrecadar();
        void def_vencedores();
        void desempate_maior_carta();
        void desempate_maior_conjunto();
        void distribuir_premiacao();
        int get_pote();
        int get_num_j_r();
        int get_num_j_p();
        int get_num_v();
        void set_num_j_r(int nj);
        void set_num_j_p(int nj);
        void set_pingo(int p);
        bool is_valid();
        void set_valid(bool b);
        void set_num_v(int nv);

        jogador jogadores_rodada[10];
    protected:
        int pote;
        int num_jogadores_r; //numero de jogadores na rodada
        int num_vencedores; //numero de vencedores
        int num_jogadores_p; //numero de jogadores na partida
        int pingo;
        bool valid;
    friend class jogador;
};

#endif