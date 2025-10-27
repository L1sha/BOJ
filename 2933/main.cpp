#include "bits/stdc++.h"

constexpr int R_MAX = 100, C_MAX = 100;

using pt = std::pair<int, int>;

int N, R, C;

std::array<std::array<char, C_MAX>, R_MAX> map;
std::bitset<R_MAX * C_MAX> visited;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> R >> C;
    
    for (int row = R - 1; row >= 0; --row) {
        
        for (int col = 0; col < C; ++col) {
            
            std::cin >> map[row][col];   
        }
    }
}

void DFS(int row, int col, std::vector<pt>& pts) {
    
    pts.push_back({row, col});
    
    std::array<pt, 4> next{{
        
        {row - 1, col},
        {row + 1, col},
        {row, col - 1},
        {row, col + 1}
    }};
    
    for (const auto& [nRow, nCol] : next) {
        
        if (nRow < 0 || nRow >= R || nCol < 0 || nCol >= C) continue;
        
        if (!visited[nRow * C + nCol] && map[nRow][nCol] == 'x') {
            
            visited[nRow * C + nCol] = true;
            DFS(nRow, nCol, pts);
        }
    }
}

bool fall(std::vector<pt>& pts) {
    
    std::sort(pts.begin(), pts.end(), [](const pt& a, const pt& b) -> bool {
        
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });
    
    int prev = -1, dist = R_MAX;
    
    for (const auto& [row, col] : pts) {
        
        if (col != prev) {
            
            prev = col;
            
            if (row == 0) return false;
            
            int newdist = 1;
            
            while (row - newdist - 1 >= 0 && map[row - newdist - 1][col] == '.') {
                
                ++newdist;
            }
            
            dist = std::min(dist, newdist);
        }
    }
    
    for (const auto& [row, col] : pts) {
        
        map[row - dist][col] = 'x';
        map[row][col] = '.';
    }
    
    return true;
}

void eraseMineral(const int& row, const int& col) {
    
    visited.reset();
    
    map[row][col] = '.';
    
    std::array<pt, 4> next{{
        
        {row - 1, col},
        {row + 1, col},
        {row, col - 1},
        {row, col + 1}
    }};
    
    for (const auto& [nRow, nCol] : next) {
        
        if (nRow < 0 || nRow >= R || nCol < 0 || nCol >= C) continue;
        
        if (!visited[nRow * C + nCol] && map[nRow][nCol] == 'x') {
            
            std::vector<std::pair<int, int>> pts;
            
            visited[nRow * C + nCol] = true;
            DFS(nRow, nCol, pts);
            
            if (fall(pts)) break;
        }
    }
}

void solve() {
    
    std::cin >> N;
    
    for (int row, left = 1; N--; ) {
        
        std::cin >> row;
        --row;
        
        if (left) {
            
            for (int col = 0; col < C; ++col) {
                
                if (map[row][col] == 'x') {
                    
                    eraseMineral(row, col);
                    break;
                }
            }
            
            left = 0;
        }
        else {
            
            for (int col = C - 1; col >= 0; --col) {
                
                if (map[row][col] == 'x') {
                    
                    eraseMineral(row, col);
                    break;
                }
            }
            
            left = 1;
        }
    }
    
    for (int row = R - 1; row >= 0; --row) {
        
        for (int col = 0; col < C; ++col) {
            
            std::cout << map[row][col];   
        }
        
        std::cout << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

