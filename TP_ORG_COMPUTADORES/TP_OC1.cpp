#include <iostream>

void reversor_string(std::string *str, int i){
    if(i >= (str->length() - i - 1)) return;
    
    std::string tmp = *str; 

    (*str)[i] = (*str)[str->length() - i - 1];
    (*str)[str->length() - i - 1] = tmp[i];
    i++;

    return reversor_string(str, i);
}

int main(){

    std::string str = "Abacaxi";
    int cpf[11] = {7, 4, 5, 4, 2, 8, 3, 4, 6, 2, 0};
    int cnpj[14] = {1, 1, 2, 2, 2, 3, 3, 3, 0, 0, 0, 1, 8, 1};
    int digit1, digit2;
    std::string valido;

    std::cout << "######REVERSOR DE STRING#######" << std::endl << std::endl;

    std::cout << "String original: " << str << std::endl;
    reversor_string(&str, 0);
    std::cout << "String reversa: " << str << std::endl << std::endl;

    std::cout << "######VERIFICADOR DE CPF/CNPJ#######" << std::endl << std::endl;

    int soma = 0;
    for(int i = 10; i > 1; i--){
        soma += cpf[10 - i] * i;
    }

    if(soma%11 < 2){
        digit1 = 0;
    }
    else{
        digit1 = 11 - soma%11;
    }

    soma = 0;
    for(int i = 11; i > 2; i--){
        soma += cpf[11 - i] * i;
    }
    soma += digit1 * 2;

    if(soma%11 < 2){
        digit2 = 0;
    }
    else{
        digit2 = 11 - soma%11;
    }

    if(digit1 == cpf[9] && digit2 == cpf[10]) valido = "valido";
    else valido = "invalido";
    
    std::cout << "CPF: " << valido << std::endl << std::endl;
    
    int num = 5;
    soma = 0;
    for(int i = 0; i < 12; i++){
        if(num == 1) num = 9;
        soma += num * cnpj[i];
        num--;
    }
    
    if(soma%11 < 2){
        digit1 = 0;
    }
    else{
        digit1 = 11 - soma%11;
    }
 
    num = 6;
    soma = 0;
    for(int i = 0; i < 12; i++){
        if(num == 1) num = 9;
        soma += num * cnpj[i];
        num--;
    }
    soma += digit1 * 2;
    std::cout << soma << std::endl;
    if(soma%11 < 2){
        digit2 = 0;
    }
    else{
        digit2 = 11 - soma%11;
    }

    if(digit1 == cnpj[12] && digit2 == cnpj[13]) valido = "valido";
    else valido = "invalido";
    
    std::cout << "CNPJ: " << valido << std::endl << std::endl;

    return 0;
}

