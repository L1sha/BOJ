#include "bits/stdc++.h"

std::vector<std::vector<std::vector<char>>> map(8, std::vector<std::vector<char>>(8, std::vector<char>(8)));
std::vector<std::vector<std::pair<int, int>>> candidates(8);


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    for (auto& row : map[0]) {
        
        for (auto& cell : row) {
            
            std::cin >> cell;
        }
    }
}

void solve() {
    
    const std::vector<char> blank(8, '.');
    
    for (int T = 1; T < 8; ++T) {
        
        map[T][0] = blank;
        
        for (int row = 1; row < 8; ++row) {
            
            map[T][row] = map[T - 1][row - 1];
        }
    }
    
    candidates[0].push_back({7, 0});
    
    for (int T = 1; T < 8; ++T) {
        
        std::vector<std::vector<bool>> visited(8, std::vector<bool>(8)); 
        
        for (const auto& [cRow, cCol] : candidates[T - 1]) {
            
            const std::array<std::pair<int, int>, 9> next{{
                
                {cRow, cCol},
                {cRow, cCol + 1},
                {cRow, cCol - 1},
                {cRow + 1, cCol},
                {cRow + 1, cCol + 1},
                {cRow + 1, cCol - 1},
                {cRow - 1, cCol},
                {cRow - 1, cCol + 1},
                {cRow - 1, cCol - 1}
            }};
            
            for (const auto& [nRow, nCol] : next) {
                
                if (nRow == 8 || nCol == -1) continue;
                
                if (map[T - 1][nRow][nCol] == '.' && map[T][nRow][nCol] == '.') {
                    
                    if (!visited[nRow][nCol]) {
                        
                        visited[nRow][nCol] = true;
                        candidates[T].push_back({nRow, nCol});
                    }
                }
            }
        }
    }
    
    if (candidates.back().empty()) std::cout << 0;
    else std::cout << 1;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

