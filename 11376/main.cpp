#include "bits/stdc++.h"


constexpr int N_MAX = 1001, M_MAX = 1001;

int N, M, sz;

std::array<std::vector<int>, N_MAX> ableWorks;
std::array<int, M_MAX> occupied;
std::bitset<N_MAX> visited;

int DFS(const int& cursor) {
    
    for (const int& next : ableWorks[cursor]) {
        
        if (!visited[next]) {
        
            if (occupied[next] == cursor) continue;
            
            visited[next] = true;
            
            if (occupied[next]) {
                
                if (DFS(occupied[next])) {
                    
                    occupied[next] = cursor;
                    return 1;
                }
            }
            else {
                
                occupied[next] = cursor;
                return 1;
            }
        }
    }
    
    return 0;
}

int solve() {
    
    int res = 0;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        visited.reset();
        
        if (DFS(idx)) {
            
            res++;
            
            visited.reset();
            
            res += DFS(idx);
        }
    }
    
    return res;
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> sz;
        ableWorks[idx].resize(sz);
        
        for (auto& el: ableWorks[idx]) std::cin >> el;
    }
    
    std::cout << solve();
    
    return 0;
}

