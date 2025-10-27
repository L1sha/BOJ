#include "bits/stdc++.h"

constexpr int N_MAX = 1000;

int N;

std::array<int, N_MAX> T, S;

bool myComp(const int& a, const int& b) {
    
    int det = S[a] * T[b] - S[b] * T[a];
    if (det == 0) return a < b;
    return det > 0;
}



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> T[idx] >> S[idx];
}

void solve() {
    
    std::vector<int> res(N);
    std::iota(res.begin(), res.end(), 0);
    
    std::sort(res.begin(), res.end(), myComp);
    
    for (const auto& el : res) std::cout << el + 1 << ' ';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}