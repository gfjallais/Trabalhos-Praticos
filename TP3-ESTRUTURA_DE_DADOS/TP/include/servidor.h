#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <fstream>
#include "caixa_de_entrada.h"

class servidor{
    public:

        servidor(int tam, std::string saida);
        ~servidor();
        void entrega_email(int id_usuario, email email);
        void apaga_email(int id_usuario, int id_email);
        void consulta_email(int id_usuario, int id_email);
        void processa_opcao(std::string str);

        caixa_de_entrada* tabela_hash;
    private:
        int tam;
        std::fstream saida;
};

#endif