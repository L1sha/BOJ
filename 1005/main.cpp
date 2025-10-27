#include "bits/stdc++.h"


int T, N, K, W;

std::vector<std::vector<int>> adjL;
std::vector<int> weight;
std::vector<std::optional<int>> memo;

int solve(int idx){
    
    if (memo[idx].has_value()) return memo[idx].value();
    if (adjL[idx].empty()) {
        
        memo[idx] = weight[idx];
        return weight[idx];
    }
    
    int max = 0;
    
    for (auto& el : adjL[idx]) max = std::max(max, solve(el));
    
    memo[idx] = weight[idx] + max;
    
    return memo[idx].value();
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--){
        
        std::cin >> N >> K;
        
        adjL.clear();
        weight.clear();
        memo.clear();
        adjL.resize(N + 1);
        weight.resize(N + 1);
        memo.resize(N + 1);
        
        for (int idx = 1; idx <= N; ++idx) std::cin >> weight[idx];
        
        int from, to;
        while (K--){
            
            std::cin >> from >> to;
            adjL[to].push_back(from);
        }
        
        std::cin >> W;
        
        std::cout << solve(W) << '\n';
    }
    
    return 0;
}



