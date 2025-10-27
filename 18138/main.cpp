#include "bits/stdc++.h"


constexpr int N_MAX = 201, M_MAX = 201;

int N, M;

std::array<int, N_MAX> width1;
std::array<int, M_MAX> width2;

std::array<std::pair<std::pair<int, int>, std::pair<int, int>>, N_MAX> edges;
std::array<int, M_MAX> occupant;
std::bitset<M_MAX> visited;

void findEdges() {
    
    for (int idx = 1; idx <= N; ++idx) {
        
        edges[idx].first.first = std::distance(width2.begin(), std::lower_bound(width2.begin() + 1, width2.begin() + M + 1, std::ceil(width1[idx] * 0.5)));
        edges[idx].first.second = std::distance(width2.begin(), std::upper_bound(width2.begin() + 1, width2.begin() + M + 1, std::floor(width1[idx] * 0.75)));
        edges[idx].second.first = std::distance(width2.begin(), std::lower_bound(width2.begin() + 1, width2.begin() + M + 1, width1[idx]));
        edges[idx].second.second = std::distance(width2.begin(), std::upper_bound(width2.begin() + 1, width2.begin() + M + 1, std::floor(width1[idx] * 1.25)));
    }
}

int solve(int idx) {
    
    for (int cand = edges[idx].first.first; cand < edges[idx].first.second; ++cand) {
        
        if (visited[cand]) continue;
        visited[cand] = true;
        
        if (occupant[cand] == 0 || solve(occupant[cand])) {
            
            occupant[cand] = idx;
            return 1;
        }
    }
    
    for (int cand = edges[idx].second.first; cand < edges[idx].second.second; ++cand) {
        
        if (visited[cand]) continue;
        visited[cand] = true;
        
        if (occupant[cand] == 0 || solve(occupant[cand])) {
            
            occupant[cand] = idx;
            return 1;
        }
    }
    
    return 0;
}

int solve() {
    
    int res = 0;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        visited.reset();
        res += solve(idx);
    }
    
    return res;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> width1[idx];
    for (int idx = 1; idx <= M; ++idx) std::cin >> width2[idx];
    
    std::sort(width2.begin() + 1, width2.begin() + M + 1);
    
    findEdges();
    
    std::cout << solve();
    
    return 0;
}

