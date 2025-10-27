#include <iostream>
#include <vector>
#include <algorithm>

int N;

std::vector<std::vector<int>> adjL, map, visited;

int DFS(int row, int col) {
    
    visited[row][col] = 1;
    int res = 1;
    
    for (auto& next : adjL[row * N + col]) {
        
        if (!visited[next / N][next % N]) res += DFS(next / N, next % N);
    }
    
    return res;
}

int main() {
    
    std::cin >> N;
    adjL.resize(N * N);
    map.resize(N, std::vector<int>(N));
    visited.resize(N, std::vector<int>(N));
    
    for (auto& el : map) {
        
        for (auto& el2 : el) {
            
            char c; std::cin >> c;
            if (c == '1') el2 = 1;
        }
    }
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < N; ++col) {
            
            if (map[row][col]) {
                
                if (row != 0 && map[row - 1][col]) {
                    
                    adjL[row * N + col].push_back((row - 1) * N + col);
                    adjL[(row - 1) * N + col].push_back(row * N + col);
                }
                
                if (col != 0 && map[row][col - 1]) {
                    
                    adjL[row * N + col].push_back(row * N + col - 1);
                    adjL[row * N + col - 1].push_back(row * N + col);
                }
            }
        }
    }
    
    std::vector<int> res;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < N; ++col) {
            
            if (map[row][col] && !visited[row][col]) {
                
                res.push_back(DFS(row, col));
            }
        }
    }
    
    std::sort(res.begin(), res.end());
    
    std::cout << res.size() << '\n';
    for (auto& el : res) std::cout << el << '\n';
    
    return 0;
}