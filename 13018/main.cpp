#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;

int N, K;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K;
}

void solve() {
    
    if (K == N) {
        
        std::cout << "Impossible";
        return;
    }
    
    std::vector<int> res(N);
    
    std::iota(res.begin(), res.end(), 1);
    
    for (int idx = 1; idx < N - K; ++idx) --res[idx];
    res[0] = N - K;
    
    for (const auto& el : res) std::cout << el << ' ';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}