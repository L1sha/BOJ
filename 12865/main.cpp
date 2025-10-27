#include "bits/stdc++.h"


int N, K;

std::array<std::array<int, 100'001>, 101> memo;
std::array<int, 101> weight;
std::array<int, 101> value;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    for (int idx = 0; idx < N; ++idx){
        
        std::cin >> weight[idx] >> value[idx];
        
        for (int idx2 = 1; idx2 <= K; ++idx2) {
            
            if (weight[idx] > idx2) memo[idx + 1][idx2] = memo[idx][idx2];
            else memo[idx + 1][idx2] = std::max(memo[idx][idx2], value[idx] + memo[idx][idx2 - weight[idx]]);
        }
    }
    
    std::cout << memo[N][K];
    
    return 0;
}


