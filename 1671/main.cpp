#include "bits/stdc++.h"


constexpr int N_MAX = 51;

int N;
std::array<int, N_MAX> size, speed, IQ;
std::array<std::vector<int>, N_MAX> eatable;
std::bitset<N_MAX> visited;
std::array<int, N_MAX> occupied;

void fill_eatable() {
    
    for (int idx = 1; idx <= N; ++idx) {
        
        for (int idx2 = 1; idx2 <= N; ++idx2) {
            
            if (idx != idx2 && size[idx] >= size[idx2] && speed[idx] >= speed[idx2] && IQ[idx] >= IQ[idx2]) {
                
                if (idx < idx2 && size[idx] == size[idx2] && speed[idx] == speed[idx2] && IQ[idx] == IQ[idx2]) continue;
                eatable[idx].push_back(idx2);
            }
        }
    }
}

int DFS(const int& cursor) {
    
    for (const auto& candidate: eatable[cursor]) {
        
        if (!visited[candidate] && occupied[candidate] != cursor) {
            
            visited[candidate] = true;
            
            if (occupied[candidate] == 0 || DFS(occupied[candidate])) {
                
                occupied[candidate] = cursor;
                return 1;
            }
        }
    }
    
    return 0;
}

int solve() {
    
    fill_eatable();
    
    int res = 0;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        visited.reset();
        
        if (DFS(idx)) {
            
            res++;
            
            visited.reset();
            
            res += DFS(idx);
        }
    }
    
    return N - res;
}




int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> size[idx] >> speed[idx] >> IQ[idx];
    
    std::cout << solve();
    
    return 0;
}

