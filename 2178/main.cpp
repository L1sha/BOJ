#include <iostream>
#include <vector>
#include <queue>

int N, M;

int main() {
    
    std::cin >> N >> M;
    
    std::vector<std::vector<int>> adjL(N * M), map(N, std::vector<int>(M)), visited(map); 
    
    for (auto& el : map) {
        
        for (auto& el2 : el) {
            
            char c; std::cin >> c;
            if (c == '1') el2 = 1;
        }
    }
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            if (map[row][col]) {
                
                if (row != 0 && map[row - 1][col]) {
                    
                    adjL[row * M + col].push_back((row - 1) * M + col);
                    adjL[(row - 1) * M + col].push_back(row * M + col);
                }
                
                if (col != 0 && map[row][col - 1]) {
                    
                    adjL[row * M + col].push_back(row * M + col - 1);
                    adjL[row * M + col - 1].push_back(row * M + col);
                }
            }
        }
    }
    
    std::queue<int> q;
    q.push(0);
    visited[0][0] = 1;
    
    for (int cursor; !q.empty(); ) {
        
        cursor = q.front();
        q.pop();
        
        for (auto& next : adjL[cursor]) {
            
            if (visited[next / M][next % M] == 0) {
                
                visited[next / M][next % M] = visited[cursor / M][cursor % M] + 1;
                q.push(next);
            }
        }
    }
    
    std::cout << visited[N - 1][M - 1];
    
    return 0;
}