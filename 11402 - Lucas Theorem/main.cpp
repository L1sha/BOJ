#include "bits/stdc++.h"

constexpr long long N_MAX = 1e18, M_MAX = 2001;

long long N, K, M;

std::array<std::array<long long, M_MAX>, M_MAX> binom;

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K >> M;
}

void fill() {
    
    for (int i = 0; i < M; ++i) {
        
        binom[i][0] = 1;
        for (int j = 1; j < i; ++j) {
            
            binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % M;
        }
        binom[i][i] = 1;
    }
}

void solve() {
    
    fill();
    
    long long res = 1;
    
    while (N || K) {
        
        res = (res * binom[N % M][K % M]) % M;
        N /= M;
        K /= M;
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}