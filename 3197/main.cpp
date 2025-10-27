#include "bits/stdc++.h"

constexpr int R_MAX = 1500, C_MAX = 1500;

int R, C, L1, L2;

std::array<std::array<char, C_MAX>, R_MAX> map;
std::vector<std::pair<int, int>> next;
std::array<int, R_MAX * C_MAX> parent;

int getParent(int cursor) {
    
    if (cursor != parent[cursor]) return parent[cursor] = getParent(parent[cursor]);
    return cursor;
}

void Union(int cursor1, int cursor2) {
    
    parent[getParent(cursor1)] = getParent(cursor2);
}

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> R >> C;
    
    for (int cnt = 0, row = 0; row < R; ++row) {
        
        for (int col = 0; col < C; ++col) {
            
            std::cin >> map[row][col];
            
            if (map[row][col] == 'L') {
                
                if (!cnt++) {
                    
                    L1 = row * C + col;
                }
                else {
                    
                    L2 = row * C + col;
                }
            }
            
            parent[row * C + col] = -1;
        }
    }
}

void DFS(int row, int col, int p) {
    
    std::array<std::pair<int, int>, 4> cand{{
        
        {row + 1, col},
        {row - 1, col},
        {row, col + 1},
        {row, col - 1}
    }};
    
    for (const auto& [nRow, nCol] : cand) {
        
        if (nRow >= 0 && nRow < R && nCol >= 0 && nCol < C) {
            
            if (parent[nRow * C + nCol] == -1) {
                
                parent[nRow * C + nCol] = p;
                
                if (map[nRow][nCol] == 'X') {
                    
                    next.push_back({nRow, nCol});
                }
                else {
                    
                    DFS(nRow, nCol, p);
                }
            }
        }
    }
}

void melt(int row, int col, std::vector<std::pair<int, int>>& newNext) {
    
    map[row][col] = '.';
    
    std::array<std::pair<int, int>, 4> cand{{
        
        {row + 1, col},
        {row - 1, col},
        {row, col + 1},
        {row, col - 1}
    }};
    
    for (const auto& [nRow, nCol] : cand) {
        
        if (nRow >= 0 && nRow < R && nCol >= 0 && nCol < C) {
            
            if (map[nRow][nCol] == 'X') {
                
                if (parent[nRow * C + nCol] == -1) {
                    
                    parent[nRow * C + nCol] = getParent(row * C + col);
                    newNext.push_back({nRow, nCol});
                }
            }
            else {
                
                if (getParent(nRow * C + nCol) != getParent(row * C + col)) {
                    
                    Union(nRow * C + nCol, row * C + col);
                }
            }
        }
    }
}

void solve() {
    
    for (int row = 0; row < R; ++row) {
        
        for (int col = 0; col < C; ++col) {
            
            if (parent[row * C + col] == -1 && map[row][col] != 'X') {
                
                parent[row * C + col] = row * C + col;
                DFS(row, col, row * C + col);
            }
        }
    }
    
    int day = 0;
    
    while (getParent(L1) != getParent(L2)) {
        
        std::vector<std::pair<int, int>> newNext;
        
        for (const auto& [row, col] : next) {
            
            melt(row, col, newNext);
        }
        
        next = std::move(newNext);
        day++;
    }
    
    std::cout << day;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

