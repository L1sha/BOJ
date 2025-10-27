#include "bits/stdc++.h"

constexpr int N_MAX = 1025;

int N, M, NODENUM = 1;

std::array<std::array<int, 2 * N_MAX>, 2 * N_MAX> seg2D;
std::array<std::array<int, N_MAX>, N_MAX> curVal;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void segUpdate2D(int row, int col, int val) {
    
    int rowCursor = NODENUM + row - 1;
    
    while (rowCursor) {
        
        int colCursor = NODENUM + col - 1;
        
        while (colCursor) {
            
            seg2D[rowCursor][colCursor] += val;
            colCursor >>= 1;
        }
        
        rowCursor >>= 1;
    }
}

int segQuery(const int& rowCursor, const int& y1, const int& y2, int colCursor = 1, int l = 1, int r = NODENUM) {
    
    if (l > y2 || r < y1) return 0;
    else if (l >= y1 && r <= y2) return seg2D[rowCursor][colCursor];
    else return segQuery(rowCursor, y1, y2, colCursor * 2, l, l + (r - l) / 2)
        + segQuery(rowCursor, y1, y2, colCursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

int segQuery2D(const int& x1, const int& x2, const int& y1, const int& y2, int rowCursor = 1, int l = 1, int r = NODENUM) {
    
    if (l > x2 || r < x1) return 0;
    else if (l >= x1 && r <= x2) return segQuery(rowCursor, y1, y2);
    else return segQuery2D(x1, x2, y1, y2, rowCursor * 2, l, l + (r - l) / 2)
        + segQuery2D(x1, x2, y1, y2, rowCursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

void get_input() {
    
    std::cin >> N >> M;
    
    while (NODENUM < N) NODENUM <<= 1;
    
    for (int row = 1; row <= N; ++row) {
        
        for (int col = 1; col <= N; ++col) {
            
            std::cin >> curVal[row][col];
            segUpdate2D(row, col, curVal[row][col]);
        }
    }
}

void solve() {
    
    for (int W, X1, Y1, X2, Y2, C; M--; ) {
        
        std::cin >> W;
        
        if (W) {
            
            std::cin >> X1 >> Y1 >> X2 >> Y2;
            std::cout << segQuery2D(X1, X2, Y1, Y2) << '\n';
        }
        else {
            
            std::cin >> X1 >> Y1 >> C;
            segUpdate2D(X1, Y1, C - curVal[X1][Y1]);
            curVal[X1][Y1] = C;
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

