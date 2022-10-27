#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H
#include <string>
#include "list_template.h"
#include "memlog.h"

int compare_given_order(std::string str1, std::string str2, int *order){
    int min_len = std::min(str1.length(), str2.length());
    int result = 0;
    int c1, c2;

    for(int i = 0; i < min_len; i++){
        result = 0;
        c1 = str1[i];
        c2 = str2[i];
        if(str1[i] >= 'a' && str1[i] <= 'z'){
            c1 = order[str1[i] - 'a'];
        }
        if(str2[i] >= 'a' && str2[i] <= 'z'){
            c2 = order[str2[i] - 'a'];
        }
        
        if(c1 < c2){
            result = -1;
        }
        else if(c1 > c2){
            result = 1;
        }

        if(result != 0) return result;
    }

    if(result == 0 && (str1.length() != str2.length())){
        if(str1.length() > str2.length()) result = 1;
        else result = - 1;
    }

    return result;
}

void swap(node<std::string> *xp, node<std::string> *yp){
    std::string temp_str = xp->get_item();
    int temp_q = xp->get_quant();
    xp->set_node(yp->get_item(), yp->get_quant());
    yp->set_node(temp_str, temp_q);
}

void selection_sort(list<std::string> *list, int start, int end, int *order){
    erroAssert(list->get_size() >= end - start, "Lista menor do que o intervalo solicitado");
    int i, j, min;
    for (i = start; i < end-1; i++){
        min = i;
        for (j = i+1; j < end; j++){
            if(compare_given_order(list->at_position(j, false)->get_item(), list->at_position(min, false)->get_item(), order) == -1){
                min = j;
            }     
        }
        LEMEMLOG((long int)((list->at_position(i, false))),sizeof(node<std::string>), 0);
        swap(list->at_position(min, false), list->at_position(i, false));
    }
}

#endif