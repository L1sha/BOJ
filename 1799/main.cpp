#include "bits/stdc++.h"


int N, bitmask;

std::array<std::vector<int>, 19> candidates;
std::array<std::array<std::optional<int>, 524288>, 19> memo;

int solve(int idx) {
    
    if (idx == 2 * N - 1) {
        
        int newbitmask = bitmask, res = 0;
        while (newbitmask) {
            
            if (newbitmask % 2) res++;
            newbitmask /= 2;
        }
        
        return res;
    }
    
    if (memo[idx][bitmask].has_value()) return memo[idx][bitmask].value();
    
    int max = 0;
    
    for (auto& el : candidates[idx]) {
        
        if ((bitmask >> el) % 2 == 0) {
            
            bitmask |= (1 << el);
            
            max = std::max(solve(idx + 1), max);
            
            bitmask &= ~(1 << el);
        }
    }
    
    max = std::max(solve(idx + 1), max);
    
    memo[idx][bitmask] = max;
    return max;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int temp;
    
    for (int row = 0; row < N; ++row) for (int col = 0; col < N; ++col) {
        
        std::cin >> temp;
        if (temp) candidates[row + col].push_back(N - 1 - row + col);
    }
    
    std::cout << solve(0);
    
    return 0;
}

