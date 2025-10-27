#include "bits/stdc++.h"


int N, M, cnt;

std::array<std::array<char, 1001>, 1001> map;
std::array<std::array<int, 1001>, 1001> isDone;
std::array<std::array<int, 1001>, 1001> visited;

void solve(int row, int col) {
    
    if (!isDone[row][col]) {
        
        if (visited[row][col]) cnt++;
        else {
            
            visited[row][col]++;
            
            switch (map[row][col]) {
                
                case 'U':
                solve(row - 1, col);
                break;
                
                case 'D':
                solve(row + 1, col);
                break;
                
                case 'L':
                solve(row, col - 1);
                break;
                
                case 'R':
                solve(row, col + 1);
                break;
            }
        }
        
        isDone[row][col] = true;
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) std::cin >> map[row][col];
    
    for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) if (!isDone[row][col]) solve(row, col);
    
    std::cout << cnt;
    
    return 0;
}

