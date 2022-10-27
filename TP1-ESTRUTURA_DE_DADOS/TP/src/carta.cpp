#include "carta.h"

carta::carta(){
    this->naipe = -1;
    this->num = -1;
}

carta::carta(std::string carta_str){
    switch (carta_str[carta_str.length() - 1]) {
        case 'P':
            this->naipe = 0;
            break;
        case 'E':
            this->naipe = 1;
            break;
        case 'C':
            this->naipe = 2;
            break;
        case 'O':
            this->naipe = 3;
            break;
    }
    this->naipe = naipe;
    int aux = stoi(carta_str.substr(0, carta_str.length() - 1));
    this->num = aux;
}

int carta::get_num(){
    return this->num;
}

int carta::get_naipe(){
    return this->naipe;
}

bool carta::operator==(carta carta){
    if(this->num == carta.get_num()){
        return true;
    }
    return false;
}

void carta::set_carta(int num){
    this->num = num;
}