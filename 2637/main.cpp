#include "bits/stdc++.h"

constexpr int N_MAX = 101;

int N, M;
std::array<std::vector<std::pair<int, int>>, N_MAX> adjL;
std::array<int, N_MAX> in, res;
std::bitset<N_MAX> visited;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    for (int from, to, weight; M--; ) {
        
        std::cin >> from >> to >> weight;
        adjL[from].push_back({to, weight});
        ++in[to];
    }
}

void solve() {
    
    std::queue<int> q;
    
    res[N] = 1;
    
    for (int idx = N; idx >= 1; --idx) {
        
        if (!visited[idx] && in[N] == 0) {
            
            q.push(idx);
            visited[idx] = true;
        }
        
        while (!q.empty()) {
            
            auto cursor = q.front();
            q.pop();
            
            for (const auto& [next, weight] : adjL[cursor]) {
                
                res[next] += res[cursor] * weight;
                
                if (--in[next] == 0) {
                    
                    q.push(next);
                    visited[next] = true;
                }
            }
            
            if (!adjL[cursor].empty()) res[cursor] = 0;
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (res[idx] != 0) {
            
            std::cout << idx << ' ' << res[idx] << '\n';
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

