#include "bits/stdc++.h"


int N, M;

const int INF = 1e9;

std::array<std::array<int, 101>, 10101> res;
/* IDEA NM = 1e9 -> TLE
        => use cost instead of memory
        : maximize memory sum under limited cost sum,
        when memory sum can exceed M ? 
*/
std::array<int, 101> memory;
std::array<int, 101> cost;

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> memory[idx];
    for (int idx = 1; idx <= N; ++idx) std::cin >> cost[idx];
    
    for (int c = 0; c <= 10100; ++c) for (int idx = 1; idx <= N; ++idx) {
        // c can be 0 !!! 
        
        if (cost[idx] <= c) {
            
            res[c][idx] = std::max(res[c - cost[idx]][idx - 1] + memory[idx], res[c][idx - 1]);
            if (res[c][idx] >= M) { std::cout << c; return 0; }
        }
        else res[c][idx] = res[c][idx - 1];
    }
    
    
    return 0;
}


