#include <iostream>
#include <sstream>
#include "msgassert.h"
#include "memlog.h"
#include "servidor.h"

int hashing(int in, int m){
    return in%m;
}

servidor::~servidor(){
    this->saida.close();
}

servidor::servidor(int tam, std::string saida){
    this->tabela_hash = new caixa_de_entrada[tam];
    this->saida.open(saida, std::ios::out);
    erroAssert(this->saida.is_open(), "Arquivo de saida nao abriu corretamente");
    this->tam = tam; 
}

void servidor::entrega_email(int id_usuario, email em){
    defineFaseMemLog(0);
    int hash = hashing(id_usuario, this->tam);
    email* e = this->tabela_hash[hash].insere(&em);
    if(e != nullptr){
        this->saida << "OK: MENSAGEM " << em.get_id_email() << " PARA " << id_usuario << " ARMAZENADA EM " << hash << "\n";
    }
    else{
        this->saida << "ERRO: MENSAGEM NÃO PÔDE SER ARMAZENADA\n";
    } 
}

void servidor::consulta_email(int id_usuario, int id_email){
    defineFaseMemLog(1);
    email* temp = this->tabela_hash[hashing(id_usuario, this->tam)].consulta(id_email);
    if(temp != nullptr){
        if(temp->get_id_email() == id_email && temp->get_id_usuario() == id_usuario){
            this->saida << "CONSULTA " << id_usuario << " " << id_email << ": " << temp->get_msg() << std::endl;
        }
        else{

            this->saida << "CONSULTA " << id_usuario << " " << id_email << ": " << "MENSAGEM INEXISTENTE\n";
        }
    }
    else{
        this->saida << "CONSULTA " << id_usuario << " " << id_email << ": " << "MENSAGEM INEXISTENTE\n";
    }
}

void servidor::apaga_email(int id_usuario, int id_email){
    defineFaseMemLog(2);
    int tmp = this->tabela_hash[hashing(id_usuario, this->tam)].apaga(id_email, id_usuario);
    if(tmp == 0){
        this->saida << "ERRO: MENSAGEM INEXISTENTE\n";
    } 
    else if(tmp == 1){
        this->saida << "OK: MENSAGEM APAGADA\n";
    } 
}

void servidor::processa_opcao(std::string str){

    std::stringstream ss(str);

    std::string opt;
    ss >> opt;

    int id_usuario, id_email;
    if(opt == "ENTREGA"){
        //Pega os ids para efetuar a operacao
        ss >> id_usuario >> id_email;

        //Lê a mensagem
        int n; ss >> n;
        std::string msg = "", temp;
        for(int i = 0; i < n; i++){
            ss >> temp;
            if(i < n - 1) msg += temp + " ";
            else msg += temp;
        }

        email em(id_email, id_usuario, msg);
        //Entrega o email ao usuário desejado
        this->entrega_email(id_usuario, em);
    }
    if(opt == "CONSULTA"){
        //Pega os ids para efetuar a operacao
        ss >> id_usuario >> id_email;
        //Faz a consulta
        this->consulta_email(id_usuario, id_email);
    }
    if(opt == "APAGA"){
        //Pega os ids para efetuar a operacao
        ss >> id_usuario >> id_email;
        //Apaga o email
        this->apaga_email(id_usuario, id_email);
    }
}