#include "rodada.h"

rodada::rodada(){
    this->pote = 0;
    this->num_vencedores = 0;
    this->num_jogadores_r = 0;
    this->num_jogadores_p = 0;
    this->pingo = 0;
    this->num_vencedores = 0;
    this->valid = true;
}
//Arrecada o dinheiro da rodada, apostas e pingo, se esta for válida, e adciona ao pote
void rodada::arrecadar(){
    for(int i = 0; i < this->num_jogadores_p; i++){
        if(this->jogadores_rodada[i].get_montante() - this->pingo - this->jogadores_rodada[i].get_aposta() < 0){
            this->set_valid(false);
        }
    }

    if(this->is_valid()){
        for(int i = 0; i < this->num_jogadores_p; i++){
            this->jogadores_rodada[i].alt_montante(-this->pingo - this->jogadores_rodada[i].get_aposta());
            this->pote += this->jogadores_rodada[i].get_aposta();
            this->pote += pingo;
        }
    }
    
    for(int i = 0; i < this->num_jogadores_p; i++){
        this->jogadores_rodada[i].aposta = 0;
    }
}

bool rodada::is_valid(){
    return valid;
}

void rodada::set_valid(bool b){
    this->valid = b;
}

void rodada::set_num_v(int nv){
    this->num_vencedores = nv;
}

void rodada::def_vencedores(){
    int min = 20;
    int max = -1;

    for(int i = 0; i < this->num_jogadores_p; i++){
        if(this->jogadores_rodada[i].jogada[0] < min){
            min = this->jogadores_rodada[i].jogada[0];
        }
    }
    for(int i = 0; i < this->num_jogadores_p; i++){
        if(this->jogadores_rodada[i].jogada[0] == min){
            this->jogadores_rodada[i].set_vencedor(true);
            this->num_vencedores++;
        }
    }
    //Desempate
    if(this->num_vencedores > 1){
        if(min == 3){
            this->desempate_maior_conjunto();
        }
        else if((min == 8) || (min == 9) || (min == 7) || (min == 4)){
            this->desempate_maior_conjunto();
            if(this->num_vencedores > 1){
                if((min == 8) || (min == 4)){
                    max = -1;
                    for(int j = 0; j < this->num_jogadores_p; j++){
                        if(this->jogadores_rodada[j].jogada[3] >= max && this->jogadores_rodada[j].eh_vencedor()){
                            max = this->jogadores_rodada[j].jogada[3];
                        }
                    }
                    for(int j = 0; j < this->num_jogadores_p; j++){
                        if(this->jogadores_rodada[j].jogada[3] != max && this->jogadores_rodada[j].eh_vencedor()){
                            this->jogadores_rodada[j].vencedor = 0;
                            this->num_vencedores--;
                        }
                    }
                }
            }
        }
        if(this->num_vencedores > 1){
            this->desempate_maior_carta();
        }
    }
}

void rodada::desempate_maior_carta(){
    int max = -1;
    for(int j = 0; j < this->num_jogadores_p; j++){
        if(this->jogadores_rodada[j].jogada[1] >= max && this->jogadores_rodada[j].eh_vencedor()){
            max = this->jogadores_rodada[j].jogada[1];
        }
    }
    
    for(int j = 0; j < this->num_jogadores_p; j++){
        if(this->jogadores_rodada[j].jogada[1] >= max && this->jogadores_rodada[j].eh_vencedor()){
            max = this->jogadores_rodada[j].jogada[1];
        }
        if(this->jogadores_rodada[j].jogada[1] != max && this->jogadores_rodada[j].eh_vencedor()){
            this->jogadores_rodada[j].vencedor = 0;
            this->num_vencedores--;
        }
    }
}

void rodada::desempate_maior_conjunto(){
    int max = -1;
    for(int j = 0; j < this->num_jogadores_p; j++){
        if(this->jogadores_rodada[j].jogada[2] >= max && this->jogadores_rodada[j].eh_vencedor()){
            max = this->jogadores_rodada[j].jogada[2];
        }
    }
    for(int j = 0; j < this->num_jogadores_p; j++){
        if(this->jogadores_rodada[j].jogada[2] != max && this->jogadores_rodada[j].eh_vencedor()){
            this->jogadores_rodada[j].set_vencedor(false);
            this->num_vencedores--;
        }
    }
}

void rodada::distribuir_premiacao(){
    for(int j = 0; j < this->num_jogadores_p; j++){
        if(this->jogadores_rodada[j].eh_vencedor()){
            this->jogadores_rodada[j].alt_montante(this->pote/num_vencedores);
        }
    }
    this->pote = 0;
}

int rodada::get_pote(){
    return this->pote;
}

int rodada::get_num_j_r(){
    return this->num_jogadores_r;
}

int rodada::get_num_j_p(){
    return this->num_jogadores_p;
}

int rodada::get_num_v(){
    return this->num_vencedores;
}

void rodada::set_num_j_r(int nj){
    this->num_jogadores_r = nj;
}

void rodada::set_num_j_p(int nj){
    this->num_jogadores_p = nj;
}

void rodada::set_pingo(int p){
    this->pingo = p;
}
