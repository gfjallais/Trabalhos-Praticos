#include "email.h"

email::email(){
    this->id_email = -1;
    this->id_usuario = -1;
    this->mensagem = "";
    this->left = nullptr;
    this->right = nullptr;
}

email::email(int id_email, int id_usuario, std::string msg){
    this->id_usuario = id_usuario;
    this->id_email = id_email;
    this->mensagem = msg;
    this->left = nullptr;
    this->right = nullptr;
}

int email::get_id_email(){
    return this->id_email;
}

int email::get_id_usuario(){
    return this->id_usuario;
}

std::string email::get_msg(){
    return this->mensagem;
}

void email::set_email(int id_e, int id_u, std::string msg){
    this->id_email = id_e;
    this->id_usuario = id_u;
    this->mensagem = msg;
}