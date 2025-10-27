#include "bits/stdc++.h"

constexpr int N_MAX = 5, K_MAX = 11;

const int PRIME = 1e9 + 7;
int N, K;

std::array<int, N_MAX + 1> loc;
std::array<std::array<long long, 4 * N_MAX>, K_MAX> segTree;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K;
    
    for (int input, idx = 0; idx < N; ++idx) {
        
        std::cin >> input;
        loc[input] = idx;
    }
}

void segInit(int cursor = 1, int l = 0, int r = N - 1) {
    
    segTree[0][cursor] = r - l + 1;
    
    if (l != r) {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1 , r);
    }
}

void segUpdate(int k, int target, int val, int cursor = 1, int l = 0, int r = N - 1) {
    
    if (target > r || target < l) return;
    
    else if (l == r) segTree[k][cursor] = val;
    
    else {
        
        segUpdate(k, target, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate(k, target, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[k][cursor] = (segTree[k][cursor * 2] + segTree[k][cursor * 2 + 1]) % PRIME;
    }
}

long long segQuery(int k, int ql, int qr = N - 1, int cursor = 1, int l = 0, int r = N - 1) {
    
    if (l > qr || r < ql) return 0;
    
    else if (l >= ql && r <= qr) return segTree[k][cursor];
    
    else {
        
        return (segQuery(k, ql, qr, cursor * 2, l, l + (r - l) / 2)
            + segQuery(k, ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r)) % PRIME;
    }
}
void solve() {
    
    segInit();
    
    for (int k = 1; k < K; ++k) {
        
        for (int idx = 1; idx <= N; ++idx) {
            
            segUpdate(k - 1, loc[idx], 0);
            segUpdate(k, loc[idx], segQuery(k - 1, loc[idx]));
        }
    }
    
    std::cout << segTree[K - 1][1];
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

