#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M, from, to, weight;
std::array<std::vector<intPair>, 501> adjL;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    while (M--) {
        
        std::cin >> from >> to >> weight;
        adjL[from].push_back({weight, to});
    }
    
    std::vector<long long> res(N + 1, 1e9), hasCycle;
    res[1] = 0;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        for (int node = 1; node <= N; ++node) if (res[node] != 1e9) {
            
            for (auto& el : adjL[node]) {
                
                res[el.second] = std::min(res[el.second], res[node] + el.first);
            }
        }
        
        if (idx == N - 1) hasCycle = res;
    }
    
    if (res != hasCycle) std::cout << -1;
    else {
            
        for (int idx = 2; idx <= N; ++idx) {
            
            if (res[idx] == 1e9) std::cout << -1 << '\n';
            else std::cout << res[idx] << '\n';
        }
    }
    
    return 0;
}

