#include <vector>

void DFS_adj(int index, std::vector<std::vector<int>> *grafo, std::vector<bool> *vis, std::vector<int> *ord);

void DFS_adj_r(int index, int num, std::vector<std::vector<int>> *grafo, std::vector<int> *scc);