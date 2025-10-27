/* 
    Total value = just # of matching
    Ring : # of nodes
    Linear : # of nodes - 1
    
    => JUST maximize matching : binary matching problem
*/



#include "bits/stdc++.h"

constexpr int N_MAX = 1000;

int N, M;

std::array<std::vector<int>, N_MAX> adjL;
std::array<int, N_MAX> occupied;
std::bitset<N_MAX> visited;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    for (int idx = 0; idx < N; ++idx) {
        
        adjL[idx].clear();
        occupied[idx] = -1;
    }
    
    for (int from, to; M--; ){
        
        std::cin >> from >> to;
        adjL[from].push_back(to);
    }
}

int DFS(int cursor) {
    
    for (const int& next : adjL[cursor]) {
        
        if (!visited[next]) {
            
            visited[next] = true;
            
            if (occupied[next] == -1 || DFS(occupied[next])) {
                
                occupied[next] = cursor;
                return 1;
            }
        }
    }
    
    return 0;
}

void solve() {
    
    int T, res;
    
    std::cin >> T;
    
    while (T--) {
        
        get_input();
        res = 0;
        
        for (int idx = 0; idx < N; ++idx) {
            
            visited.reset();
            res += DFS(idx);
        }
        
        std::cout << res << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    solve();
    
    return 0;
}

