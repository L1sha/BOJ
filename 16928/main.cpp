#include "bits/stdc++.h"


int N, M, res = 1e9;

std::unordered_map<int, int> jump;
std::array<bool, 101> visited;
std::array<int, 101> min;

void solve(int pos, int dist) {
    
    if (pos == 100) {
        
        res = std::min(res, dist);
        return;
    }
    
    if (min[pos] <= dist) return;
    min[pos] = dist;
    
    visited[pos] = true;
    
    for (int dice = 1; dice <= 6; ++dice) {
        
        if (pos + dice <= 100 && !visited[jump[pos + dice]]) solve(jump[pos + dice], dist + 1);
    }
    
    visited[pos] = false;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    int from, to;
    
    for (int idx = 1; idx <= 100; ++idx) jump[idx] = idx;
    std::fill(min.begin(), min.end(), 1e9);
    
    while (N--) {
        
        std::cin >> from >> to;
        jump[from] = to;
    }
    
    while (M--) {
        
        std::cin >> from >> to;
        jump[from] = to;
    }
    
    solve(1, 0);
    
    std::cout << res;
    
    return 0;
}

