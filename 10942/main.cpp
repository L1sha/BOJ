#include "bits/stdc++.h"


int N, M;

std::array<int, 2001> nums;
std::array<std::array<std::optional<int>, 2001>, 2001> memo;

int isP(int start, int end){
    
    if (memo[start][end].has_value()) return memo[start][end].value();
    
    if (start == end) { memo[start][end] = 1; return 1; }
    if (end == start + 1) { 
        
        if (nums[start] == nums[end]) { memo[start][end] = 1; return 1; }
        else { memo[start][end] = 0; return 0; }
    }
    
    if (nums[start] == nums[end] && isP(start + 1, end - 1)) { memo[start][end] = 1; return 1; }
    else { memo[start][end] = 0; return 0; }
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 1; idx <= N; ++idx) std::cin >> nums[idx];
    
    int start, end;
    
    std::cin>> M;
    while (M--){
        
        std::cin >> start >> end;
        std::cout << isP(start, end) << '\n';
    }
    
    return 0;
}


