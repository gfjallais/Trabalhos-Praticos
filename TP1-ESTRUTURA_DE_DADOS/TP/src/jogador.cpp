#include "jogador.h"

//Retorna true se as cartas na lista p (mao auxiliar do jogador), são uma sequência.
bool seguido(lista *p){
    erroAssert(p->get_tam() != 0, "Lista vazia");
    node* q = p->get_primeiro()->prox;
    int arr[13] = {0};
    int count = 0;
    while(q != NULL){
        arr[q->item.get_num() - 1] = 1;
        q = q->prox;
    }
    for(int i = 0; i < 14; i++){
        if(arr[i] == 1){
            while(arr[(i%13)] == 1){
                i++;
                count++;
            }
        }
        if(count == 5){
            return true;
        }
        count = 0;
    }
    return false;
}

//Retorna a carta com o maior número na lista p
int max_element(lista *p){
    erroAssert(p->get_tam() != 0, "Lista vazia");
    int max = -1;
    node* q = p->get_primeiro();
    while(q != NULL){
        if(q->item.get_num() > max){
            max = q->item.get_num();
        }
        q = q->prox;
    }
    return max;
}

jogador::jogador(){}

jogador::jogador(std::string nome, int dinheiro_inicial, carta *mao){
    int aux = mao[0].get_naipe();
    this->_nome = nome;
    this->montante = dinheiro_inicial;
    this->msm_naipe = 1;
    for(int i = 0; i < 5; i++){
        if(mao[i].get_naipe() != aux) this->msm_naipe = 0;
        this->v_mao[i] = mao[i];
    }
    this->define_mao();
    this->vencedor = 0;
    this->num_vitorias = 0;
    this->aposta = 0;
}

void jogador::set_mao(carta *mao){
    int aux = mao[0].get_naipe();
    for(int i = 0; i < 5; i++){
        if(mao[i].get_naipe() != aux) this->msm_naipe = 0;
        this->v_mao[i] = mao[i];
    }
}

int jogador::get_montante(){
    return this->montante;
}

void jogador::alt_montante(int n){
    this->montante += n;
}

std::string jogador::get_nome(){
    return this->_nome;
}

int jogador::get_categoria_jogada(){
    return this->jogada[0];
}

void jogador::set_vencedor(bool b){
    this->vencedor = b;
}
 
bool jogador::eh_vencedor(){
    return vencedor;
}

void jogador::set_aposta(int aposta){
    this->aposta = aposta;
}

int jogador::get_aposta(){
    return this->aposta;
}

bool jogador::operator==(jogador j){
    if(this->_nome == j.get_nome()){
        return true;
    }
    return false;
}

void jogador::define_mao(){
    lista mao_aux;
    carta carta_aux;
    carta_aux.num = 1;
    int aux_vector[13] = {0};
    int list_s = 0;
    for(int i = 0; i < 5; i++){
        if(aux_vector[this->v_mao[i].get_num() - 1] == 0){
            aux_vector[this->v_mao[i].get_num() - 1] = 1;
        }
    }
    for(int i = 0; i < 13; i++){
        if(aux_vector[i] == 1) list_s++;
    }
    for(int i = 0; i < 5; i++){
        mao_aux.insere(this->v_mao[i]);
    }
    this->jogada[1] = max_element(&mao_aux);
    this->jogada[0] = 10;
    switch (list_s) {
        case 5:
            {
                int temp = 1;
                if(this->msm_naipe){
                    for(int i = 9; i < 14; i++){
                        carta_aux.num = (i%13) + 1;
                        if(mao_aux.pesquisa(&carta_aux) == NULL){
                            temp = 0;
                            break;
                        }
                    }
                    if(temp){
                        this->jogada[0] = 1;
                        return;
                    }
                    for(int i = 10; i < 15; i++){
                        carta_aux.num = (i%13) + 1;
                        if(mao_aux.pesquisa(&carta_aux) != NULL){
                            temp = 1;
                            break;
                        }
                    }
                    if(seguido(&mao_aux) && temp == 0){
                        this->jogada[0] = 2;
                        return;
                    }
                    if(!seguido(&mao_aux)){
                        this->jogada[0] = 5;
                        return;
                    }
                }
                if(seguido(&mao_aux)){
                    this->jogada[0] = 6; 
                    return;
                }
                break;
            }
        case 4:
            {
                this->jogada[0] = 9; //One Pair
                int max_pair = -1;
                node* p = mao_aux.get_primeiro();
                while(p != NULL){
                    if(p->quantidade == 2){
                        max_pair = p->item.get_num();
                    }
                    p = p->prox;
                }
                this->jogada[2] = max_pair;
                return;
            }
        case 3:
            {
                bool qtd_3 = 0;
                node* p = mao_aux.get_primeiro();
                while(p != NULL){
                    if(p->quantidade == 3){
                        qtd_3 = 1;
                        break;
                    }
                    p = p->prox;
                } 
                if(qtd_3){
                    this->jogada[0] = 7;
                    this->jogada[2] = p->item.get_num();
                    return;
                }
                else{
                    this->jogada[0] = 8; // Two Pairs
                    node* p = mao_aux.get_primeiro();
                    carta vet[2];
                    int i = 0;
                    while(p != NULL){
                        if(p->quantidade == 2){
                            vet[i] = p->item;
                            i++;
                        }
                        p = p->prox;
                    }
                    if(vet[0].get_num() >= vet[1].get_num()){
                        this->jogada[2] = vet[0].get_num();
                        this->jogada[3] = vet[1].get_num();
                        return;
                    }
                    else{
                        this->jogada[2] = vet[1].get_num();
                        this->jogada[3] = vet[0].get_num();
                        return;
                    }
                    break; 
                }
            }
        case 2:
            {
                node* p = mao_aux.get_primeiro()->prox;
                while(p != NULL){
                    if(p->quantidade == 4){
                        this->jogada[0] = 3; // Four of a Kind
                        this->jogada[2] = p->item.get_num();
                        return;
                    }
                    if(p->quantidade == 3){
                        this->jogada[0] = 4; // Full House
                        this->jogada[2] = p->item.get_num(); 
                    }
                    if(p->quantidade == 2){
                        this->jogada[3] = p->item.get_num();
                    }
                    p = p->prox;
                }
                return;
            }
        default:
            break;
    }
}
