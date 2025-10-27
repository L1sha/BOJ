#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;
const int PRIME = 1e9 + 7;

using intPair = std::pair<int, int>;

int N;

std::array<std::array<int, 4 * N_MAX>, 11> segTrees;
std::array<intPair, N_MAX> A;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> A[idx].first;
        A[idx].second = idx;
    }
    
    std::sort(A.begin(), A.begin() + N, [](intPair A, intPair B) -> bool {
        
        if (A.first == B.first) return A.second > B.second;
        return A.first < B.first;
    });
}

void segUpdate(int cursor, int l, int r, int target, int value, int dim) {
    
    if (target < l || target > r) return;
    
    if (l == r) segTrees[dim][cursor] = value;
    else {
        
        segUpdate(cursor * 2, l, l + (r - l) / 2, target, value, dim);
        segUpdate(cursor * 2 + 1, l + (r - l) / 2 + 1, r, target, value, dim);
        
        segTrees[dim][cursor] = (segTrees[dim][cursor * 2] + segTrees[dim][cursor * 2 + 1]) % PRIME;
    }
}

int segQuery(int cursor, int l, int r, int ql, int qr, int dim) {
    
    if (r < ql || l > qr) return 0;
    
    if (r <= qr && l >= ql) return segTrees[dim][cursor];
    
    return (segQuery(cursor * 2, l, l + (r - l) / 2, ql, qr, dim) + 
    segQuery(cursor * 2 + 1, l + (r - l) / 2 + 1, r, ql, qr, dim)) % PRIME;
}

void solve() {
    
    for (int idx = 0; idx < N; ++idx) {
        
        segUpdate(1, 0, N - 1, A[idx].second, 1, 0);
        
        if (A[idx].second == 0) continue;
        
        for (int dim = 1; dim < 11; ++dim) {
            
            segUpdate(1, 0, N - 1, A[idx].second, segQuery(1, 0, N - 1, 0, A[idx].second - 1, dim - 1), dim);
        }
    }
    
    std::cout << segQuery(1, 0, N - 1, 0, N - 1, 10);
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

