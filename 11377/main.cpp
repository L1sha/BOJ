#include "bits/stdc++.h"


constexpr int N_MAX = 1001, M_MAX = 1001;

int N, M, K, cnt;

std::array<std::vector<int>, N_MAX> ableWorks;
std::array<int, M_MAX> occupied;
std::array<int, N_MAX> matchedWorks;
std::bitset<M_MAX> visited;

int DFS(const int& cursor) {
    
    for (const auto& work: ableWorks[cursor]) {
        
        if (!visited[work] && occupied[work] != cursor) {
            
            visited[work] = true;
            
            if (occupied[work]) {
                
                if (DFS(occupied[work])) {
                    
                    occupied[work] = cursor;
                    return 1;
                }
            }
            else {
                
                occupied[work] = cursor;
                return 1;
            }
        }
    }
    
    return 0;
}

int solve() {
    
    int res = 0;
    cnt = 0;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        visited.reset();
        
        res += DFS(idx);
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        visited.reset();
        
        if (DFS(idx)) {
            
            res++;
            
            if (++cnt == K) break;
        }
    }
    
    return res;
}



int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> K;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> cnt;
        ableWorks[idx].resize(cnt);
        
        for (auto& el: ableWorks[idx]) std::cin >> el;
    }
    
    std::cout << solve();
    
    return 0;
}

