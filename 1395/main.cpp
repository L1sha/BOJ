#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N, M;

std::array<int, N_MAX * 4> segTree;
std::bitset<N_MAX * 4> lazy;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
}

void lazyUpdate(const int& cursor, const int& l, const int& r) {
    
    if (lazy[cursor]) {
        
        segTree[cursor] = r - l + 1 - segTree[cursor];
        
        if (l != r) {
            
            lazy[cursor * 2] = !lazy[cursor * 2];
            lazy[cursor * 2 + 1] = !lazy[cursor * 2 + 1];
        }
        
        lazy[cursor] = false;
    }
}

void segUpdate(const int& ql, const int& qr, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (r < ql || l > qr) return;
    else if (r <= qr && l >= ql) {
        
        segTree[cursor] = r - l + 1 - segTree[cursor];
        
        if (l != r) {
            
            lazy[cursor * 2] = !lazy[cursor * 2];
            lazy[cursor * 2 + 1] = !lazy[cursor * 2 + 1];
        }
    }
    else {
        
        segUpdate(ql, qr, cursor * 2, l, l + (r - l) / 2);
        segUpdate(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = segTree[cursor * 2] + segTree[cursor * 2 + 1];
    }
}

int segQuery(const int& ql, const int& qr, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (r < ql || l > qr) return 0;
    if (r <= qr && l >= ql) return segTree[cursor];
    else return segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2) + segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

void solve() {
    
    for (int O, S, T; M--; ) {
        
        std::cin >> O >> S >> T;
        
        switch (O) {
            
            case 0:
            
            segUpdate(S, T);
            
            break;
            
            case 1:
            
            std::cout << segQuery(S, T) << '\n';
            
            break;
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

