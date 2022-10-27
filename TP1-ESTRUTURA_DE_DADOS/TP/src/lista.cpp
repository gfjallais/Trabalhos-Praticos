#include "lista.h"

node::node(){
    this->prox = NULL;
    this->quantidade = 1;
}

void node::q_increment(){
    this->quantidade++;
}

lista::lista(){
    this->primeiro = new node();
    this->ultimo = this->primeiro;
    this->tam = 0;
}

lista::~lista(){
    this->limpa();
}

node* lista::posiciona(int pos, bool antes){
    erroAssert((pos < this->tam) || (pos >= 0), "ERRO: Posicao invalida");
    node *p;
    
    p = this->get_primeiro();
    for(int i = 0; i < pos; i++){
        p = p->prox;
    }
    if(!antes){
        p = p->prox;
    }
    return p;
}

carta lista::get_item(int pos){
    erroAssert((pos < this->tam) || (pos >= 0), "ERRO: Posicao invalida");
    node* p;
    p = this->posiciona(pos, false);
    return p->item;
}

void lista::set_item(carta item, int pos){
    erroAssert((pos < this->tam) || (pos >= 0), "ERRO: Posicao invalida");
    node* p;
    p = this->posiciona(pos, false);
    p->item = item;
}

void lista::insere(carta item){
    node *p;
    p = this->primeiro;
    bool flag = false;
    while(p != NULL){
        if(p->item == item){
            p->q_increment();
            flag = true;
            break;
        }
        p = p->prox;
    }
    if(!flag){
        p = new node();
        p->item = item;
        this->ultimo->prox = p;
        this->ultimo = p;
        this->tam++;
    }
}

node* lista::pesquisa(carta *item){
    node *p;

    p = this->primeiro;
    while(p != NULL){
        if(p->item == *item){
            break;
        }
        p = p->prox;
    }
    return p;
}

void lista::limpa(){
    node* p;
    p = this->primeiro->prox;

    while(p!=NULL) {   
        this->primeiro->prox = p->prox;
        delete p;
        p = this->primeiro->prox;
    }
    this->ultimo = this->primeiro;
    this->tam = 0;
}

int lista::get_tam(){
    return this->tam;
}

node* lista::get_primeiro(){
    return this->primeiro;
}