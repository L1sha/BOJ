#include "bits/stdc++.h"

constexpr int N_MAX = 10'000, INF = 1e9;

int N, T, M, S, E;

std::array<int, N_MAX> dist;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> T >> M >> S >> E;
}

void solve() {
    
    std::fill(dist.begin(), dist.begin() + N, INF);
    dist[S] = 0;
    
    for (int from, to, weight, t = 1; t <= T; ++t) {
        
        std::vector<std::pair<int, int>> toUpdate;
        toUpdate.reserve(2 * M);
        
        for (int idx = 0; idx < M; ++idx) {
            
            std::cin >> from >> to >> weight;
            
            if (dist[from] != INF && dist[to] > dist[from] + weight) {
                
                toUpdate.push_back({to, dist[from] + weight});
            }
            
            if (dist[to] != INF && dist[from] > dist[to] + weight) {
                
                toUpdate.push_back({from, dist[to] + weight});
            }
        }
        
        for (const auto& [target, val] : toUpdate) {
            
            dist[target] = std::min(dist[target], val);
        }
    }
    
    if (dist[E] == INF) std::cout << -1;
    else std::cout << dist[E];
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

