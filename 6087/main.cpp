#include "bits/stdc++.h"

constexpr int W_MAX = 100, H_MAX = 100;

const int MAX = 1e9;

using pt = std::pair<int, int>;

int W, H;

std::array<std::array<char, W_MAX>, H_MAX> map;
pt start, end;
std::array<std::array<bool, W_MAX>, H_MAX> visited;
std::array<std::array<std::array<int, 4>, W_MAX>, H_MAX> best;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> W >> H;
    
    for (int cnt = 0, row = 0; row < H; ++row) {
        
        for (int col = 0; col < W; ++col) {
            
            std::cin >> map[row][col];
            
            if (map[row][col] == 'C') {
                
                if (!cnt++) {
                    
                    start = {row, col};
                }
                else {
                    
                    end = {row, col};
                }
            }
            
            best[row][col] = {MAX, MAX, MAX, MAX};
        }
    }
}

void DFS(int row, int col, int dir, int cnt, int& res) {
    
    if (row == end.first && col == end.second) {
        
        res = std::min(res, cnt);
        return;
    }
    
    if (dir >= 0) {
        
        if (best[row][col][dir] <= cnt) return;
        best[row][col][dir] = cnt;
    }
    
    visited[row][col] = true;
    
    std::array<pt, 4> next{{
        
        {row, col + 1},
        {row + 1, col},
        {row, col - 1},
        {row - 1, col}
    }};
    
    for (int nDir = 0; nDir < 4; ++nDir) {
        
        auto& [nRow, nCol] = next[nDir];
        
        if (nRow < 0 || nRow == H || nCol < 0 || nCol == W) continue;
        
        if (!visited[nRow][nCol] && map[nRow][nCol] != '*') {
            
            if (dir == -1 || dir == nDir) {
                
                DFS(nRow, nCol, nDir, cnt, res);
            }
            else {
                
                DFS(nRow, nCol, nDir, cnt + 1, res);
            }
        }
    }
    
    visited[row][col] = false;
}

void solve() {
    
    int res = MAX;
    
    DFS(start.first, start.second, -1, 0, res);
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

