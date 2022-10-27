#ifndef LIST_H
#define LIST_H
#include "msgassert.h"

//Define a estrutura de dados list, para auxiliar a processar a entrada
template <class T>
class node{

    public:
        node<T>();
        void q_increment();
        T get_item();
        int get_quant();
        node<T>* get_next();
        node<T>* get_prev();
        void set_node(T item, int quant);

        node<T> *next;
        node<T> *prev;
        T item;
        int quant;

};

template <class T>
class list{

    public:
        list();
        ~list();
        node<T>* get_head();
        node<T>* get_tail();
        T get_item(int pos);
        void insert(T item, bool count_duplicates);
        node<T>* search(T *item);
        node<T>* at_position(int pos, bool before);
        int get_size();

    private:
        node<T>* head;
        node<T>* tail;
        int size;

};

template <class T>
node<T>::node(){
    this->next = NULL;
    this->quant = 1;
    this->prev = NULL;
}

template <class T>
T node<T>::get_item(){
    return this->item;
}

template <class T>
node<T>* node<T>::get_next(){
    return this->next;
}

template <class T>
node<T>* node<T>::get_prev(){
    return this->prev;
}

template <class T>
int node<T>::get_quant(){
    return this->quant;
}

template <class T>
void node<T>::q_increment(){
    this->quant++;
}

template <class T>
void node<T>::set_node(T item, int quant){
    this->item = item;
    this->quant = quant;
}

template <class T>
list<T>::list(){
    this->head = new node<T>();
    this->tail = this->head;
    this->size = 0;
}

template <class T>
list<T>::~list(){
    node<T>* p;
    p = this->head->next;

    while(p!=NULL) {   
        this->head->next = p->next;
        delete p;
        p = this->head->next;
    }
    this->tail = this->head;
    this->size = 0;
}

template <class T>
node<T>* list<T>::get_head(){
    return this->head;
}

template <class T>
node<T>* list<T>::get_tail(){
    return this->tail;
}

template <class T>
T list<T>::get_item(int pos){
    erroAssert((pos < this->size) || (pos >= 0), "ERRO: Posicao invalida");
    node<T>* p;
    p = this->at_position(pos, false);
    return p->item;
}

template <class T>
void list<T>::insert(T item, bool count_duplicates){
    node<T> *p;
    if(count_duplicates){
        p = this->head;
        while(p != NULL){
            if(p->item == item){
                p->q_increment();
                return;
            }
            p = p->next;
        }
    }
    p = new node<T>();
    p->item = item;
    this->tail->next = p;
    p->prev = this->tail;
    this->tail = p;
    this->size++;
}

template <class T>
node<T>* list<T>::search(T *item){
    node<T>* p;

    p = this->head;
    while(p != NULL){
        if(p->item == *item){
            break;
        }
        p = p->next;
    }
    return p;
}

template <class T>
node<T>* list<T>::at_position(int pos, bool before){
    erroAssert((pos < this->size) || (pos >= 0), "ERRO: Posicao invalida");
    node<T>* p;
    if(pos <= this->size/2){
        p = this->get_head();
        for(int i = 0; i < pos; i++){
            p = p->next;
        }
        if(!before){
            p = p->next;
        }
    }
    else{
        p = this->get_tail();
        for(int i = 0; i < this->size - pos - 1; i++){
            p = p->prev;
        }
        if(before){
            p = p->next;
        }
    }
    
    return p;
}

template <class T>
int list<T>::get_size(){
    return this->size;
}

#endif