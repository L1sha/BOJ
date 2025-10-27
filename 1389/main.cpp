#include "bits/stdc++.h"

constexpr int N_MAX = 101;

int N, M;

std::array<std::array<int, N_MAX>, N_MAX> dist;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        for (int idx2 = 1; idx2 <= N; ++idx2) {
            
            dist[idx][idx2] = 1e9;
        }
        
        dist[idx][idx] = 0;
    }
    
    for (int from, to; M--; ) {
        
        std::cin >> from >> to;
        
        dist[from][to] = 1;
        dist[to][from] = 1;
    }
}

void solve() {
    
    for (int mid = 1; mid <= N; ++mid) {
        
        for (int start = 1; start <= N; ++start) {
            
            for (int end = 1; end <= N; ++end) {
                
                dist[start][end] = std::min(dist[start][end], dist[start][mid] + dist[mid][end]);
            }
        }
    }
    
    int min = 1e9, res;
    
    for (int sum, idx = 1; idx <= N; ++idx) {
        
        sum = 0;
        
        for (int idx2 = 1; idx2 <= N; ++idx2) {
            
            sum += dist[idx][idx2];
        }
        
        if (sum < min) {
            
            res = idx;
            min = sum;
        }
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

