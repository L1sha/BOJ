#include "bits/stdc++.h"

constexpr int N_MAX = (1 << 20) - 1;

std::array<int, N_MAX> res;
std::array<int, N_MAX * 4> segTree;

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void init() {
    
    for (int idx = 1, K = 1; idx < N_MAX; ++idx) {
        
        if (idx >= (1 << (K + 1)) - 1) ++K;
        
        res[idx] = res[idx - ((1 << K) - 1)] + K;
    }
}

void segInit(int cursor = 1, int l = 0, int r = N_MAX - 1) {
    
    if (l == r) segTree[cursor] = res[l];
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = std::max(segTree[cursor * 2], segTree[cursor * 2 + 1]);
    }
}

int segQuery(int ql, int qr, int cursor = 1, int l = 0, int r = N_MAX - 1) {
    
    if (l > qr || r < ql) return 0;
    else if (l >= ql && r <= qr) return segTree[cursor];
    else {
        
        return std::max(segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2),
            segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r));
    }
}

int query(int l, int r, int c = 0) {
    
    if (r < N_MAX) {
        
        return segQuery(l, r) + c;
    }
    
    int K = 1;
    
    while (r >= (1 << (K + 1)) - 1) ++K;
    
    int mid = (1 << K) - 1;
    
    if (l >= mid) {
        
        return query(l - mid, r - mid, K) + c;
    }
    else {
        
        return std::max(query(l, mid - 1, 0), query(0, r - mid, K)) + c;
    }
}

void solve() {
    
    init();
    segInit();
    
    int T, X, Y;
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> X >> Y;
        std::cout << query(X, Y) << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    solve();
    
    return 0;
}