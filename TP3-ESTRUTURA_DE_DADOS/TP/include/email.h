#ifndef EMAIL_H
#define EMAIL_H
#include <string>

class email{

    public:
        email();
        email(int id_email, int id_usuario, std::string msg);
        int get_id_email();
        int get_id_usuario();
        std::string get_msg();
        void set_email(int id_e, int id_u, std::string msg);
    
    protected:
        email *left;
        email *right;
        int id_email;
        int id_usuario;
        std::string mensagem;
    friend class caixa_de_entrada;
};

#endif