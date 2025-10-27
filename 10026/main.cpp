#include "bits/stdc++.h"

constexpr int N_MAX = 100;

int N;

std::array<std::array<char, N_MAX>, N_MAX> map;
std::array<std::bitset<N_MAX>, N_MAX> visited;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < N; ++col) {
            
            std::cin >> map[row][col];
        }
    }
}

void DFS(int row, int col) {
    
    std::array<std::pair<int, int>, 4> next{{
        
        {row + 1, col},
        {row - 1, col},
        {row, col + 1},
        {row, col - 1}
    }};
    
    for (auto& [nRow, nCol] : next) {
        
        if (nRow < 0 || nRow == N || nCol < 0 || nCol == N) continue;
        
        if (!visited[nRow][nCol] && map[nRow][nCol] == map[row][col]) {
            
            visited[nRow][nCol] = true;
            DFS(nRow, nCol);
        }
    }
}

void solve() {
    
    int res = 0;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < N; ++col) {
            
            if (!visited[row][col]) {
                
                visited[row][col] = true;
                DFS(row, col);
                res++;
            }
        }
    }
    
    std::cout << res << ' ';
    res = 0;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < N; ++col) {
            
            if (map[row][col] == 'G') map[row][col] = 'R';
        }
        
        visited[row].reset();
    }
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < N; ++col) {
            
            if (!visited[row][col]) {
                
                visited[row][col] = true;
                DFS(row, col);
                res++;
            }
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

