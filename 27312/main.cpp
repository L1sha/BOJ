#include "bits/stdc++.h"

constexpr int N_MAX = 1000;

int M, Q, N;

std::array<int, N_MAX + 1> A;

void get_input() {
    
    std::cin >> M >> Q >> N;
    for (int idx = 1; idx <= N; ++idx) std::cin >> A[idx];
}

void solve() {
    
    std::vector<int> res;
    
    for (int input, idx = 1; idx <= M; ++idx) {
        
        std::cout << "? " << idx << ' ' << idx << std::endl;
        std::cin >> input;
        
        res.push_back(input != 1 ? input - 1 : 2);
    }
    
    std::cout << "!";
    for (const auto& el : res) std::cout << ' ' << el;
    for (int idx = M; idx < N; ++idx) std::cout << ' ' << 1;
    std::cout << std::endl;
}



int main(int argc, char** argv) {
    
    get_input();
    solve();
    
    return 0;
}