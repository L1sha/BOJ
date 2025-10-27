#include "bits/stdc++.h"

constexpr int NMQ_MAX = 200'000;

int N, M, Q;

std::vector<int> A, left, right;
std::vector<bool> used;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> Q;
    
    A.resize(N);
    for (auto& el : A) std::cin >> el;
    
    left.resize(M);
    for (auto& el : left) {
        
        std::cin >> el;
        --el;
    }
    
    right.resize(M);
    for (auto& el : right) {
        
        std::cin >> el;
        --el;
    }
    
    used.resize(N);
}

void solve() {
    
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    
    std::priority_queue<std::pair<int, int>> pq;
    
    for (int rightmost = -1, idx = 0; idx < M; ++idx) {
        
        if (left[idx] > right[idx]) {
            
            while (Q--) std::cout << 1'000'000'000 << '\n';
            return;
        }
        
        left[idx] = std::max(rightmost + 1, left[idx]);
        
        for (int idx2 = left[idx]; idx2 <= right[idx]; ++idx2) {
            
            used[idx2] = true;
            pq.push({A[idx2], idx2});
        }
        
        rightmost = right[idx];
    }
    
    for (int i, j; Q--; ) {
        
        std::cin >> i >> j;
        --i;
        --j;
        
        std::swap(A[i], A[j]);
        
        if (used[i]) pq.push({A[i], i});
        if (used[j]) pq.push({A[j], j});
        
        while (A[pq.top().second] != pq.top().first) pq.pop();
        
        std::cout << pq.top().first << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}