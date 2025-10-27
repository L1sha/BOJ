#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M, S, E, L;
const int MAX = 1e9;
std::array<std::vector<intPair>, 201> adjL;
std::array<std::array<int, 201>, 201> adjM;
std::bitset<201> visited;

void FW() {
    
    for (int middle = 1; middle <= N; ++middle) {
        
        for (int start = 1; start <= N; ++start) {
            
            for (int end = 1; end <= N; ++end) {
                
                adjM[start][end] = std::min(adjM[start][end], adjM[start][middle] + adjM[middle][end]);
            }
        }
    }
}

double ignite(int cursor) {
    
    std::vector<intPair> nodes(N);
    
    for (int idx = 1; idx <= N; ++idx) {
        
        nodes[idx - 1] = {adjM[cursor][idx], idx};
    }
    
    std::sort(nodes.begin(), nodes.end());
    
    double res = 0, remaining;
    
    for (const auto& [dist, node] : nodes) {
        
        res = std::max(res, (double)dist);
        visited[node] = true;
        
        for (const auto& [dist2, node2] : adjL[node]) {
            
            if (visited[node] && visited[node2]) {
                
                remaining = dist2 - (adjM[cursor][node] - adjM[cursor][node2]);
                res = std::max(res, adjM[cursor][node] + remaining * 0.5);
            }
        }
    }
    
    visited.reset();
    
    return res;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(1);
    
    std::cin >> N >> M;
    
    for (int row = 1; row <= N; ++row) {
        
        for (int col = 1; col <= N; ++col) {
            
            adjM[row][col] = MAX;
        }
        
        adjM[row][row] = 0;
    }
    
    while (M--) {
        
        std::cin >> S >> E >> L;
        
        adjL[S].push_back({L, E});
        adjL[E].push_back({L, S});
        adjM[S][E] = std::min(L, adjM[S][E]);
        adjM[E][S] = std::min(L, adjM[E][S]);
    }
    
    FW();
    
    double res = MAX;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        res = std::min(ignite(idx), res);
    }
    
    std::cout << res;
    
    return 0;
}

