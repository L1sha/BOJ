#include "bits/stdc++.h"

constexpr int N_MAX = 1000, M_MAX = 1000, K_MAX = 10, INF = 1e9;

int N, M, K;

std::array<std::array<std::bitset<K_MAX + 1>, M_MAX>, N_MAX> visited;

std::array<std::bitset<N_MAX>, N_MAX> map;

struct Node {
    
    int dist, row, col, wall;
};


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> K;
    
    char c;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            std::cin >> c;
            
            if (c == '0') map[row][col] = true;
            else map[row][col] = false;
        }
    }
}
void solve() {
    
    if (N == 1 && M == 1) {
        
        std::cout << 1;
        return;
    }
    
    std::queue<Node> q;
    q.push({1, 0, 0, 0});
    
    visited[0][0][0] = true;
    
    while (!q.empty()) {
        
        auto [cDist, cRow, cCol, cWall] = q.front();
        q.pop();
        
        int nDist = cDist + 1, nWall = cWall;
        
        std::array<std::pair<int, int>, 4> next{{
            
            {cRow - 1, cCol},
            {cRow + 1, cCol},
            {cRow, cCol - 1},
            {cRow, cCol + 1}
        }};
        
        for (const auto& [nRow, nCol] : next) {
            
            nWall = cWall;
            
            if (nRow < 0 || nRow == N || nCol < 0 || nCol == M) continue;
            
            if (nRow == N - 1 && nCol == M - 1) {
                
                std::cout << nDist;
                return;
            }
            
            if (!map[nRow][nCol]) {
                
                if (nWall++ == K) continue;
            }
            
            if (!visited[nRow][nCol][nWall]) {
                
                visited[nRow][nCol][nWall] = true;
                
                q.push({nDist, nRow, nCol, nWall});
            }
        }
    }
    
    std::cout << -1;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}