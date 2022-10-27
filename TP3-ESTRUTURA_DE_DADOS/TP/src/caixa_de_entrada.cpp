#include <iostream>
#include "caixa_de_entrada.h"
#include "memlog.h"

caixa_de_entrada::caixa_de_entrada(){
    this->root = nullptr;
}

caixa_de_entrada::~caixa_de_entrada(){
    limpa(this->root);
}

void caixa_de_entrada::limpa(email* n){
    if (n == nullptr) return;

    limpa(n->left);
    limpa(n->right);

    LEMEMLOG((long int)(n),sizeof(email*), 0);

    delete n;
}

email* caixa_de_entrada::insere(email *e){
    return insere_recursivo(e, this->root);
}

email* caixa_de_entrada::insere_recursivo(email *e, email* &atual){
    if(atual == nullptr){
        atual = new email(e->id_email, e->id_usuario, e->mensagem);
        ESCREVEMEMLOG((long int)(atual),sizeof(email*), 0);
        return atual;
    }
 
    if (e->get_id_email() < atual->get_id_email()) {
        atual->left = insere_recursivo(e, atual->left);
    }

    else if(e->get_id_email() > atual->get_id_email()) {
        atual->right = insere_recursivo(e, atual->right);
    }

    return atual;
}

email* caixa_de_entrada::pesquisa(int id_email, bool pai){
    email* p = this->root;
    email* q = nullptr;

    while(p != nullptr && p->get_id_email() != id_email){
        if(p->get_id_email() > id_email){
            q = p;
            p = p->left;
        }
        else if(p->get_id_email() < id_email){
            q = p;
            p = p->right;
        }
        if(q != nullptr) LEMEMLOG((long int)(q),sizeof(email*), 0);
        if(p != nullptr) LEMEMLOG((long int)(p),sizeof(email*), 0);
    }

    if(pai) return q;
    return p;
}

email* caixa_de_entrada::get_sucessor(email* atual){
    if(atual->right != nullptr) return this->min_val(atual->right);

    email* succ = nullptr;
    email* p = this->root;
    while(p != nullptr && atual != nullptr){
        if(atual->get_id_email() < p->get_id_email()){
            succ = p;
            p = p->left;
        }
        else if(atual->get_id_email() > p->get_id_email()){
            p = p->right;
        }
        else break;
    }
    if(succ == nullptr && p != nullptr && p->right == nullptr) succ = p;
    return succ;
}

email* caixa_de_entrada::min_val(email* atual){
    while (atual->left != nullptr) {
        atual = atual->left;
    }
    return atual;
}

int caixa_de_entrada::apaga(int id_email, int id_usuario){
    email* pai = nullptr, *atual = nullptr;
    atual = this->pesquisa(id_email, false);

    if(atual != this->root) pai = this->pesquisa(id_email, true);

    if (atual == nullptr || atual->get_id_email() != id_email || atual->get_id_usuario() != id_usuario) {
        return 0;
    }
 
    // Caso 1: Email a ser deletado é folha
    if (atual->left == nullptr && atual->right == nullptr){
        if (atual != this->root){
            if (pai->left == atual) {
                pai->left = nullptr;
            }
            else {
                pai->right = nullptr;
            }
        }
        else {
            this->root = nullptr;
        }
        LEMEMLOG((long int)(atual),sizeof(email*), 0);
        delete atual;
        return 1;
    }
 
    // Case 2: Email a ser deletado tem dois filhos
    else if (atual->left != nullptr && atual->right != nullptr){

        email* successor = this->get_sucessor(atual);
 
        int temp_id_em = successor->get_id_email();
        int temp_id_us = successor->get_id_usuario();
        std::string temp_str = successor->get_msg();
 
        apaga(successor->get_id_email(), successor->get_id_usuario());
    
        atual->set_email(temp_id_em, temp_id_us, temp_str);
    }
 
    // Case 3: Email a ser deletado tem apenas um filho
    else {
        email* filho = (atual->left)? atual->left: atual->right;

        if (atual != root){
            if (atual == pai->left) {
                pai->left = filho;
            }
            else {
                pai->right = filho;
            }
        }

        else {
            root = filho;
        }

        LEMEMLOG((long int)(atual),sizeof(email*), 0);
        delete atual;
        return 1;
    }

    return 1;
}


email* caixa_de_entrada::consulta(int id_email){
    return this->pesquisa(id_email, false);
}