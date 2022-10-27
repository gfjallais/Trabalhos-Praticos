#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "selection_sort.h"

void partition(list<std::string> *list_p, int left, int right, int *i, int *j, int m, int* order){
    *i = left; *j = right;
    std::string pivot = list_p->at_position((*i+*j)/2, false)->get_item();

    if(m <=  right - left){
        int num_words = 0;
        list<std::string> aux_list;
        while(num_words < m){
            aux_list.insert(list_p->at_position(left+num_words, false)->get_item(), false);
            num_words++;
        }
        selection_sort(&aux_list, 0, aux_list.get_size(), order);
        pivot = aux_list.at_position(aux_list.get_size()/2, false)->get_item();
    }

    do{
        while(compare_given_order(pivot, list_p->at_position(*i, false)->get_item(), order) == 1) (*i)++;
        while(compare_given_order(pivot, list_p->at_position(*j, false)->get_item(), order) == -1) (*j)--;
        if(*i <= *j){
            swap(list_p->at_position(*i, false), list_p->at_position(*j, false));
            (*i)++;
            (*j)--;
        }
    }while(*i <= *j);
}

void quicksort(list<std::string> *list, int left, int right, int m, int s, int* order){
    erroAssert(list->get_size() >= right - left, "Lista menor do que o intervalo solicitado");
    for(int k = left; k < right; k++){
        LEMEMLOG((long int)((list->at_position(k, false))),sizeof(node<std::string>), 0);
    }
    if(right - left <= s && right - left > 0) selection_sort(list, left, right, order);
    
    int i, j;

    partition(list, left, right, &i, &j, m, order);
    
    if(left < j) quicksort(list, left, j, m, s, order);
    if(i < right) quicksort(list, i, right, m, s, order);
}

#endif