#include <iostream>
#include <vector>
#include "algoritmos.hpp"



int main() {
  
    int num_seguidores; // 1 <= num_seguidores <= 1000
    int num_propostas; // 1 <= num_propostas <= 10000
    int proposta1, proposta2; // 0 <= num_propostas <= num_propostas

    while(std::cin >> num_seguidores >> num_propostas){
        

        if(num_seguidores == 0 && num_propostas == 0) break;
        
        int max = num_propostas * 2;

        // Flag para dizer se o problema é satisfazível
        bool sat = true;

        // Listas de adjacência para representar o grafo
        std::vector<std::vector<int>> adj_l(max), adj_l_r(max);

        // Vetor para a ordem topológica do grafo
        std::vector<int> top_ord;

        // Vetor que diz a qual componente conexo pertence cada vértice do grafo
        std::vector<int> scc(max, -1);

        // Vetor auxiliar a DFS utilizada no algoritmo
        std::vector<bool> visitado(max, false);

        // Criando o grafo para o 2-SAT
        for(int i = 0; i < num_seguidores; i++){

            // cada seguidor deve escolher 4 propostas
            // 2 para manter e 2 para retirar do plano

            // Os valores negados ficam na posição n + num_propostas, onde n é a posição
            // do valor não negado

            std::cin >> proposta1 >> proposta2;
            if(proposta1 && proposta2){
                adj_l[num_propostas + proposta1 - 1].emplace_back(proposta2 - 1);
                adj_l[num_propostas + proposta2 - 1].emplace_back(proposta1 - 1);
                adj_l_r[proposta1-1].emplace_back(num_propostas + proposta2 - 1);
                adj_l_r[proposta2-1].emplace_back(num_propostas + proposta1 - 1);
            }

            if(proposta1 == 0 && proposta2){
                for(int i = 0; i < max; i++){
                    if(i != proposta2 - 1){
                        adj_l[i].emplace_back(proposta2 - 1);
                        adj_l_r[proposta2 - 1].emplace_back(i);
                    } 
                }
            }

            else if(proposta1 && proposta2 == 0){
                for(int i = 0; i < max; i++){
                    if(i != proposta1 - 1){
                        adj_l[i].emplace_back(proposta1 - 1);
                        adj_l_r[proposta1 - 1].emplace_back(i);
                    } 
                }
            }
            
            std::cin >> proposta1 >> proposta2;

            if(proposta1 && proposta2){
                adj_l[proposta1-1].emplace_back(num_propostas + proposta2 - 1);
                adj_l[proposta2-1].emplace_back(num_propostas + proposta1 - 1);
                adj_l_r[num_propostas + proposta1 - 1].emplace_back(proposta2 - 1);
                adj_l_r[num_propostas + proposta2 - 1].emplace_back(proposta1 - 1);
            }

            if(proposta1 == 0 && proposta2){
                for(int i = 0; i < max; i++){
                    if(i != num_propostas + proposta2 - 1){
                        adj_l[i].emplace_back(num_propostas + proposta2 - 1);
                        adj_l_r[num_propostas + proposta2 - 1].emplace_back(i);
                    } 
                }
            }

            else if(proposta1 && proposta2 == 0){
                for(int i = 0; i < max; i++){
                    if(i != num_propostas + proposta1 - 1){
                        adj_l[i].emplace_back(num_propostas + proposta1 - 1);
                        adj_l_r[num_propostas + proposta1 - 1].emplace_back(i);
                    } 
                }
            }
        }
        
        // DFS para gerar a ordem topológica
        for(int i = 0; i < int(adj_l.size()); i++) {
            if(visitado[i] == 0) DFS_adj(i, &adj_l, &visitado, &top_ord);
        }

        // DFS na lista de adjacência com a direção inversa de incidencia de arestas
        // para encontrar os componentes conexos usando Kosaraju
        int aux = 0;
        for(int i = 0; i < int(adj_l_r.size()); i++){
            int temp = top_ord[max - i - 1];
            if(scc[temp] == -1){
                DFS_adj_r(temp, aux++, &adj_l_r, &scc);
            }
        }

        // Checa se um vértice com valor x está no mesmo componente conexo que !x
        for(int i = 0; i < num_propostas; i++){
            if(scc[i] == scc[i+num_propostas]) sat = false;
        }

        if(sat) std::cout << "sim" << std::endl;
        else std::cout << "nao" << std::endl;
    }
}