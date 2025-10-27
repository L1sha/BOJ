#include "bits/stdc++.h"

constexpr int N_MAX = 5000;

int N, M, Q;

std::array<std::array<long long, N_MAX + 2>, N_MAX + 2> fenwick;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> Q;
}

void update(int row, int col, long long val) {
    
    while (row <= N) {
        
        int col2 = col;
        
        while (col2 <= M) {
            
            fenwick[row][col2] += val;
            
            col2 += (col2 & -col2);
        }
        
        row += (row & -row);
    }
}

long long query(int row, int col) {
    
    long long res = 0;
    
    while (row > 0) {
        
        int col2 = col;
        
        while (col2 > 0) {
            
            res += fenwick[row][col2];
            
            col2 -= (col2 & -col2);
        }
        
        row -= (row & -row);
    }
    
    return res;
}

void solve() {
    
    int q, x1, y1, x2, y2, d;
    
    while (Q--) {
        
        std::cin >> q;
        
        if (q == 1) {
            
            std::cin >> x1 >> y1 >> x2 >> y2 >> d;
            
            update(x1, y1, d);
            update(x1, y2 + 1, -d);
            update(x2 + 1, y1, -d);
            update(x2 + 1, y2 + 1, d);
        }
        else {
            
            std::cin >> x1 >> y1;
            
            std::cout << query(x1, y1) << '\n';
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}