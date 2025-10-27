#include "bits/stdc++.h"

constexpr int N_MAX = 500'000;

int N, M;

std::array<int, N_MAX> A;
std::array<int, N_MAX * 4> segTree, lazy;


void segInit(int cursor = 1, int l = 0, int r = N - 1) {
    
    if (l == r) segTree[cursor] = A[l];
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = segTree[cursor * 2] ^ segTree[cursor * 2 + 1];
    }
}

void lazyUpdate(const int& cursor, const int& l, const int& r) {
    
    if (lazy[cursor]) {
        
        if ((r - l) % 2 == 0) segTree[cursor] = segTree[cursor] ^ lazy[cursor];
        
        if (l != r) {
            
            lazy[cursor * 2] = lazy[cursor * 2] ^ lazy[cursor];
            lazy[cursor * 2 + 1] = lazy[cursor * 2 + 1] ^ lazy[cursor];
        }
        
        lazy[cursor] = 0;
    }
}

void segUpdate(const int& ql, const int& qr, const int& k, int cursor = 1, int l = 0, int r = N - 1) {
    
    lazyUpdate(cursor, l, r);
    
    if (qr < l || ql > r) return;
    else if (qr >= r && ql <= l) {
        
        if ((r - l) % 2 == 0) segTree[cursor] = segTree[cursor] ^ k;
        
        if (l != r) {
            
            lazy[cursor * 2] = lazy[cursor * 2] ^ k;
            lazy[cursor * 2 + 1] = lazy[cursor * 2 + 1] ^ k;
        }
    }
    else {
        
        segUpdate(ql, qr, k, cursor * 2, l, l + (r - l) / 2);
        segUpdate(ql, qr, k, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = segTree[cursor * 2] ^ segTree[cursor * 2 + 1];
    }
}

int segQuery(const int& ql, const int& qr, int cursor = 1, int l = 0, int r = N - 1) {
    
    lazyUpdate(cursor, l, r);
    
    if (qr < l || ql > r) return 0;
    else if (qr >= r && ql <= l) return segTree[cursor];
    else {
        
        int left = segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2);
        int right = segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        return left ^ right;
    }
}

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> A[idx];
}

void solve() {
    
    segInit();
    
    std::cin >> M;
    
    for (int query, i, j, k; M--; ) {
        
        std::cin >> query;
        
        switch (query) {
            
            case 1:
            
            std::cin >> i >> j >> k;
            segUpdate(i, j, k);
            
            break;
            
            case 2:
            
            std::cin >> i >> j;
            std::cout << segQuery(i, j) << '\n';
            
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

