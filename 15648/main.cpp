#include "bits/stdc++.h"

constexpr int N_MAX = 5e5;

int N, K, D;

std::array<int, N_MAX> modMax;
std::array<int, N_MAX * 4> segTree;

void segUpdate(const int& target, const int& val, int cursor = 1, int l = 1, int r = N_MAX) {
    
    if (l > target || r < target) return;
    
    else if (l == r) segTree[cursor] = val;
    
    else {
        
        segUpdate(target, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate(target, val, cursor * 2 + 1, l + (r - l) / 2 + 1 , r);
        
        segTree[cursor] = std::max(segTree[cursor * 2], segTree[cursor * 2  + 1]);
    }
}

int segQuery(const int& ql, const int& qr, int cursor = 1, int l = 1, int r = N_MAX) {
    
    if (l > qr || r < ql) return 0;
    
    else if (l >= ql && r <= qr) return segTree[cursor];
    
    else {
        
        return std::max(segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2),
            segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r));
    }
}

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K >> D;
}

void solve() {
    
    for (int res, ql, qr, input, idx = 0; idx < N; ++idx) {
        
        std::cin >> input;
        
        ql = std::max(1, input - D);
        qr = std::min(N_MAX, input + D);
        
        res = 1 + std::max(modMax[input % K], segQuery(ql, qr));
        
        modMax[input % K] = res;
        segUpdate(input, res);
    }
    
    std::cout << segTree[1];
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

