#include "bits/stdc++.h"


int T, N;

std::array<int, 501> pages;
std::array<int, 501> partialSum;



int solve(int left, int right, std::vector<std::vector<std::optional<int>>>& memo){
    
    if (left == right) return 0;
    if (memo[left][right].has_value()) return memo[left][right].value();
    
    int min = 1234567890, temp = 0;
    
    for (int idx = left; idx < right; ++idx){
        
        temp = solve(left, idx, memo) + solve(idx + 1, right, memo);
        if (min > temp) min = temp;
    }
    
    memo[left][right] = min + partialSum[right + 1] - partialSum[left];
    
    return memo[left][right].value();
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    
    while (T--){
        
        std::cin >> N;
        for (int idx = 0; idx < N; ++idx) { std::cin >> pages[idx]; partialSum[idx + 1] = partialSum[idx] + pages[idx]; }
        
        std::vector<std::vector<std::optional<int>>> memo(N);
        for (auto& el : memo) el.resize(N);
        
        std::cout << solve(0, N - 1, memo) << '\n';
    }
    
    return 0;
}



