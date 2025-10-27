#include "bits/stdc++.h"

constexpr int N_MAX = 50;

const int INF = 2500;

int N;
int sRow = -1, sCol, sDir, res = INF;

std::array<std::array<char, N_MAX>, N_MAX> map;
std::array<std::array<std::array<int, 4>, N_MAX>, N_MAX> dp;
std::array<std::pair<int, int>, 4> move{{
    
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 0}
}};


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
            
            if (map[row][col] == '#' && sRow == -1) {
                
                sRow = row;
                sCol = col;
                
                map[row][col] = '.';
            }
            
            for (int dir = 0; dir < 4; ++dir) {
                
                dp[row][col][dir] = INF;
            }
        }
    }
}

void DFS(int, int, int, int);

void doDFS(int cnt, int row, int col, int dir) {
    
    int nDir, nCnt;
    
    if (map[row][col] == '.') {
        
        nDir = dir;
        nCnt = cnt;
    }
    else if (map[row][col] == '1') {
        
        if (dir == 0) nDir = 1;
        else if (dir == 1) nDir = 0;
        else if (dir == 2) nDir = 3;
        else if (dir == 3) nDir = 2;
        nCnt = cnt + 1;
    }
    else if (map[row][col] == '2') {
        
        if (dir == 0) nDir = 3;
        else if (dir == 3) nDir = 0;
        else if (dir == 2) nDir = 1;
        else if (dir == 1) nDir = 2;
        nCnt = cnt + 1;
    }
    
    int nRow = row + move[nDir].first, nCol = col + move[nDir].second;
    
    if (nRow != -1 && nRow != N && nCol != -1 && nCol != N && map[nRow][nCol] != '*') {
        
        DFS(nCnt, nRow, nCol, nDir);
    }
}

void DFS(int cnt = 0, int row = sRow, int col = sCol, int dir = sDir) {
    
    if (map[row][col] == '#') {
        
        res = std::min(res, cnt);
        return;
    }
    
    if (dp[row][col][dir] <= cnt) return;
    
    dp[row][col][dir] = cnt;
    
    if (map[row][col] == '!') {
        
        map[row][col] = '.';
        doDFS(cnt, row, col, dir);
        
        map[row][col] = '1';
        doDFS(cnt, row, col, dir);
        
        map[row][col] = '2';
        doDFS(cnt, row, col, dir);
        
        map[row][col] = '!';
    }
    else {
        
        doDFS(cnt, row, col, dir);
    }
}

void solve() {
    
    for (int dir = 0; dir < 4; ++dir) {
        
        sDir = dir;
        DFS();
    }
    
    std::cout << res;
}

int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}