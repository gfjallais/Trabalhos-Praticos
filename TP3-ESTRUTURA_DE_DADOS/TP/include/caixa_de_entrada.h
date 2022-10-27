#ifndef CAIXA_DE_ENTRADA_H
#define CAIXA_DE_ENTRADA_H

#include "email.h"

//Arvore binária
class caixa_de_entrada{
    public:

        caixa_de_entrada();
        ~caixa_de_entrada();
        email* insere(email *email);
        email* insere_recursivo(email *e, email* &atual);
        int apaga(int id_email, int id_usuario);
        email* consulta(int id_email);
        email* pesquisa(int id_email, bool pai);
        email* get_sucessor(email* atual);
        void limpa(email* n);
        email* min_val(email* atual);

    protected:
        email* root;
    friend class servidor;
};

#endif