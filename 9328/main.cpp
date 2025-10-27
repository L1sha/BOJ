#include "bits/stdc++.h"


int T, N, M;

bool isAvailable(int row, int col, const std::vector<std::vector<char>>& map, const std::vector<bool>& keys, const std::vector<std::vector<bool>>& visited){
    
    if (row < 0 || row >= N) return false;
    if (col < 0 || col >= M) return false;
    
    if (visited[row][col]) return false;
    
    if (map[row][col] == '*') return false;
    else if (map[row][col] == '$' || map[row][col] == '.') return true;
    else if (map[row][col] >= 'a' && map[row][col] <= 'z') return true;
    else return keys[(int)map[row][col] - 'A'];
}

void solve(int row, int col, std::vector<std::vector<char>>& map, std::vector<bool>& keys, std::vector<std::vector<bool>>& visited, int& res){
    
    visited[row][col] = true;

    if (map[row][col] == '$') res++;
    else if (map[row][col] >= 'a' && map[row][col] <= 'z') keys[(int)map[row][col] - 'a'] = true;
    
    map[row][col] = '.';
    
    if (isAvailable(row + 1, col, map, keys, visited)) solve(row + 1, col, map, keys, visited, res);
    if (isAvailable(row - 1, col, map, keys, visited)) solve(row - 1, col, map, keys, visited, res);
    if (isAvailable(row, col + 1, map, keys, visited)) solve(row, col + 1, map, keys, visited, res);
    if (isAvailable(row, col - 1, map, keys, visited)) solve(row, col - 1, map, keys, visited, res);
}   



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--){
        
        std::cin >> N >> M;
        
        std::vector<std::vector<char>> map(N, std::vector<char>(M));
        for (auto& el : map) for (auto& el2 : el) std::cin >> el2;
        
        std::vector<bool> keys(26);
        
        std::string myKey;
        std::cin >> myKey;
        if (myKey != "0") for (auto& el : myKey) keys[(int)el - 'a'] = true;
        
        std::vector<std::vector<bool>> visited(N, std::vector<bool>(M));
        std::vector<std::vector<bool>> previous;
    
        int res = 0;
        
        do {
            
            previous = visited;
            std::fill(visited.begin(), visited.end(), std::vector<bool>(M));
            
            for (int row = 0; row < N; ++row) {
                
                if (isAvailable(row, 0, map, keys, visited)) solve(row, 0, map, keys, visited, res);
                if (isAvailable(row, M - 1, map, keys, visited)) solve(row, M - 1, map, keys, visited, res);
            }
            
            for (int col = 1; col < M - 1; ++col) {
                
                if (isAvailable(0, col, map, keys, visited)) solve(0, col, map, keys, visited, res);
                if (isAvailable(N - 1, col, map, keys, visited)) solve(N - 1, col, map, keys, visited, res);
            }
            
        } while (previous != visited);
        
        std::cout << res << '\n';
    }
    
    return 0;
}


