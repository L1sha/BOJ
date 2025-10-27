#include "bits/stdc++.h"

constexpr int N_MAX = 129;

int N, K, xRow, xCol, cnt = 0;

const std::array<int, 8> pow2{1, 2, 4, 8, 16, 32, 64, 128};
const std::array<std::pair<int, int>, 4> dir{{
    
    {-1, -1},
    {-1, 1},
    {1, 1},
    {1, -1}
}};

std::array<std::array<int, N_MAX>, N_MAX> res;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> K;
    N = pow2[K];
    
    std::cin >> xCol >> xRow;
    xRow = N + 1 - xRow;
    res[xRow][xCol] = -1;
}

void fill(int size, int sRow, int sCol, int dirIdx) {
    
    if (size == 1) {
        
        res[sRow][sCol] = ++cnt;
        res[sRow + dir[dirIdx].first][sCol] = cnt;
        res[sRow][sCol + dir[dirIdx].second] = cnt;
    }
    else {
        
        fill(size - 1, sRow, sCol, dirIdx);
        
        int nRow = sRow, nCol = sCol, nDirIdx = dirIdx;
        
        nRow = nRow - dir[nDirIdx].first * pow2[size - 2];
        nCol = nCol - dir[nDirIdx].second * pow2[size - 2];
        
        fill(size - 1, nRow, nCol, nDirIdx);
        
        nRow = sRow + dir[dirIdx].first;
        nCol = sCol;
        nDirIdx = 3 - dirIdx;
        nRow = nRow - dir[nDirIdx].first * pow2[size - 2];
        nCol = nCol - dir[nDirIdx].second * pow2[size - 2];
        
        fill(size - 1, nRow, nCol, nDirIdx);
        
        nRow = sRow;
        nCol = sCol + dir[dirIdx].second;
        nDirIdx = (dirIdx + 1) % 2 + (dirIdx / 2) * 2;
        nRow = nRow - dir[nDirIdx].first * pow2[size - 2];
        nCol = nCol - dir[nDirIdx].second * pow2[size - 2];
        
        fill(size - 1, nRow, nCol, nDirIdx);
    }
}

void findX(int size, int sRow, int sCol) {
    
    if (size == 0) return;
    
    int dir;
    
    if (xRow < sRow + pow2[size - 1]) {
        
        if (xCol < sCol + pow2[size - 1]) {
            
            findX(size - 1, sRow, sCol);
            dir = 0;
        }
        else {
            
            findX(size - 1, sRow, sCol + pow2[size - 1]);
            dir = 1;
        }
    }
    else {
        
        if (xCol < sCol + pow2[size - 1]) {
            
            findX(size - 1, sRow + pow2[size - 1], sCol);
            dir = 3;
        }
        else {
            
            findX(size - 1, sRow + pow2[size - 1], sCol + pow2[size - 1]);
            dir = 2;
        }
    }
    
    sRow = sRow + pow2[size - 1] - dir / 2;
    sCol = sCol + pow2[size - 1] - ((dir + 1) % 4) / 2;
    
    fill(size, sRow, sCol, dir);
}

void solve() {
    
    findX(K, 1, 1);
    
    for (int row = 1; row <= N; ++row) {
        
        for (int col = 1; col <= N; ++col) {
            
            std::cout << res[row][col] << ' ';
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

