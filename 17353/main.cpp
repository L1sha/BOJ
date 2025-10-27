#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N, Q, L, R, X;

std::array<long long, N_MAX * 4> segTree, lazy1, lazy2;
// lazy1 : count & lazy2 : offset sum
std::array<int, N_MAX> A;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> A[idx];
}

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) segTree[cursor] = A[l];
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = segTree[cursor * 2] + segTree[cursor * 2 + 1];
    }
}

void lazyUpdate(int cursor, int l, int r) {
    
    if (lazy1[cursor] != 0) {
        
        if (l != r) {
            
            lazy2[cursor * 2] += lazy2[cursor];
            lazy2[cursor * 2 + 1] += lazy2[cursor];
            
            lazy1[cursor * 2] += lazy1[cursor];
            lazy1[cursor * 2 + 1] += lazy1[cursor];
            lazy2[cursor * 2 + 1] += lazy1[cursor] * ((r - l) / 2 + 1);
        }
        
        segTree[cursor] += lazy1[cursor] * (r - l + 1) * (r - l + 2) / 2;
        lazy1[cursor] = 0;
        
        segTree[cursor] += lazy2[cursor] * (r - l + 1);
        lazy2[cursor] = 0;
    }
}

void segUpdate(int ql, int qr, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);   
    
    if (qr < l || ql > r) return;
    
    if (r <= qr && l >= ql) {
        
        segTree[cursor] += (r - l + 1) * (r - l + 2) / 2;
        segTree[cursor] += (l - ql) * (r - l + 1);
        
        if (l != r) {
            
            lazy1[cursor * 2]++;
            lazy1[cursor * 2 + 1]++;
            lazy2[cursor * 2] += l - ql;
            lazy2[cursor * 2 + 1] += l - ql + (r - l) / 2 + 1;
        }
    }
    else {
        
        segUpdate(ql, qr, cursor * 2, l, l + (r - l) / 2);
        segUpdate(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = segTree[cursor * 2] + segTree[cursor * 2 + 1];
    }
}

long long segQuery(int X, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);   
    
    if (X < l || X > r) return 0;
    
    if (l == r) return segTree[cursor];
    
    return segQuery(X, cursor * 2, l, l + (r - l) / 2) + segQuery(X, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

void solve() {
    
    segInit();
    
    std::cin >> Q;
    
    for (int query, L, R, X; Q--; ) {
        
        std::cin >> query;
        
        switch (query) {
            
            case 1:
            
            std::cin >> L >> R;
            segUpdate(L, R);
            break;
            
            case 2:
            
            std::cin >> X;
            std::cout << segQuery(X) << '\n';
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

