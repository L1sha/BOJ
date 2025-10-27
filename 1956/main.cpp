#include "bits/stdc++.h"


int V, E;

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> V >> E;
    
    int from, to, weight;
    
    std::vector<std::vector<int>> res(V + 1, std::vector<int>(V + 1, 1e9));
    for (int idx = 1; idx <= V; ++idx) res[idx][idx] = 0;
    
    for (int idx = 0; idx < E; ++idx) {
        
        std::cin >> from >> to >> weight;
        res[from][to] = weight;
    }
    
    for (int mid = 1; mid <= V; ++mid) for (int start = 1; start <= V; ++start) for (int end = 1; end <= V; ++end) {
        
        res[start][end] = std::min(res[start][end], res[start][mid] + res[mid][end]);
    }
    
    int min = 1e9;
    
    for (int start = 1; start <= V; ++start) for (int end = start + 1; end <= V; ++end) {
        
        min = std::min(min, res[start][end] + res[end][start]);
    }
    
    if (min == 1e9) min = -1;
    std::cout << min;
    
    return 0;
}

