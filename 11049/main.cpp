#include "bits/stdc++.h"


int N;
int r, c;
std::array<std::pair<int, int>, 501> matSize;
std::array<std::array<std::optional<int>, 501>, 501> memo;

int solve (int left, int right){
    
    if (left == right) return 0;
    if (memo[left][right].has_value()) return memo[left][right].value();
    
    long long min = 1e10, temp;
    
    for (int idx = left; idx < right; ++ idx){
        
        temp = solve(left, idx) + solve(idx + 1, right) + matSize[left].first * matSize[idx].second * matSize[right].second;
        if (temp < min) min = temp;
    }
    
    memo[left][right] = min;
    return min;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> matSize[idx].first >> matSize[idx].second;
    
    std::cout << solve(0, N - 1);
    
    return 0;
}


