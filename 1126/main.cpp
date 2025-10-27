#include "bits/stdc++.h"


constexpr int N_MAX = 50, H_MAX = 500'000;

int N;

std::array<int, N_MAX> block;
std::array<std::optional<int>, H_MAX * 2 + 1> memo, prev;

void get_input() {
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> block[idx];
}

void insert(int height, int val) {
    
    if (memo[height].has_value()) memo[height] = std::max(memo[height].value(), val);
    else memo[height] = val;
}


void solve() {
    
    for (int idx = 0; idx < N; ++idx) {
        
        insert(H_MAX + block[idx], block[idx]);
        insert(H_MAX - block[idx], 0);
        
        for (int idx2 = 0; idx2 < H_MAX * 2 + 1; ++idx2) {
            
            if (prev[idx2].has_value()) {
                
                insert(idx2 + block[idx], prev[idx2].value() + block[idx]);
                insert(idx2 - block[idx], prev[idx2].value());
            }
        }
        
        prev = memo;
    }
    
    if (memo[H_MAX].has_value()) std::cout << memo[H_MAX].value();
    else std::cout << -1;
}



int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    get_input();
    
    solve();
    
    return 0;
}

