#ifndef LISTA_H
#define LISTA_H
#include "msgassert.h"
#include "carta.h"

//Define a estrutura de dados lista, para auxiliar em operações na classe jogador

class node{
    public:
        node();
        void q_increment();
        node *prox;
        carta item;
        int quantidade;
};

class lista{
    public:
        lista();
        ~lista();
        node* get_primeiro();
        carta get_item(int pos);
        void set_item(carta item, int pos);
        void insere(carta item);
        node* pesquisa(carta *item);
        void limpa();
        node* posiciona(int pos, bool antes);
        int get_tam();
    private:
        node* primeiro;
        node* ultimo;
        int tam;
};

#endif