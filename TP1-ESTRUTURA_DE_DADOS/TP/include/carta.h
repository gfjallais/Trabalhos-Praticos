#ifndef CARTA_H
#define CARTA_H
#include <string>

//Define a classe carta, para representar as cartas do baralho

class carta{
    public:
        carta();
        carta(std::string carta_str);
        int get_num();
        int get_naipe();
        bool operator==(const carta);
        void set_carta(int num);
        
    protected:
        int naipe; // P = 0, E = 1, C = 2, O = 3
        int num; // 1 a 13
    friend class jogador;
};

#endif