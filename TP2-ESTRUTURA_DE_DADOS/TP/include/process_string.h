#ifndef PROCESS_STRING_H
#define PROCESS_STRING_H

#include<iostream>
#include<string>

bool check_prohibited_chars(char c){
    if(c == ',' || c == '.' || c == '!' || c == '?' 
        || c == ':' || c == ';' || c == '_' || c == ' '){
            return false;
    }
    return true;
}

void process_string(std::string *str){
    for(long unsigned int i = 0; i < str->length(); i++){
        if(!check_prohibited_chars((*str)[i])){
            str->erase(i, 1);
            i--;
        }
        else (*str)[i] = std::tolower((*str)[i]);
    }
}


#endif