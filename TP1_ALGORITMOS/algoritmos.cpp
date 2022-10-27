#include "algoritmos.hpp"

void DFS_adj(int index, std::vector<std::vector<int>> *grafo, std::vector<bool> *vis, std::vector<int> *ord){
    
    (*vis)[index] = true;

    for(auto v : (*grafo)[index]){
        if((*vis)[v] == 0) DFS_adj(v, grafo, vis, ord);
    }

    ord->push_back(index);
}

void DFS_adj_r(int index, int num, std::vector<std::vector<int>> *grafo, std::vector<int> *scc){
    
    (*scc)[index] = num;

    for(auto v : (*grafo)[index]){

        if((*scc)[v] == -1){
            DFS_adj_r(v, num, grafo, scc);
        }

    }
}