#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M, R;


std::vector<int> res;
std::vector<int> item;
std::vector<std::vector<int>> adjM;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> R;
    
    res.resize(N + 1, 0);
    item.resize(N + 1);
    adjM.resize(N + 1, std::vector<int>(N + 1, 1e9));
    for (int idx = 1; idx <= N; ++idx)
        adjM[idx][idx] = 0;
    
    for (int idx = 1; idx <= N; ++idx)
        std::cin >> item[idx];
    
    int from, to, weight;
    while (R--) {
        
        std::cin >> from >> to >> weight;
        adjM[from][to] = std::min(adjM[from][to], weight);
        adjM[to][from] = std::min(adjM[to][from], weight);
    }
    
    for (int mid = 1; mid <= N; ++mid)
        for (int start = 1; start <= N; ++start)
            for (int end = 1; end <= N; ++end)
                adjM[start][end] = std::min(adjM[start][end], adjM[start][mid] + adjM[mid][end]);
    
    for (int idx = 1; idx <= N; ++idx)
        for (int idx2 = 1; idx2 <= N; ++idx2)
            if (adjM[idx][idx2] <= M) res[idx] += item[idx2];
    
    std::cout << *std::max_element(res.begin(), res.end());
    
    return 0;
}


