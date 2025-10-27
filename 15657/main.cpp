#include "bits/stdc++.h"


int N, M, cursor = 0;

std::array<int, 8> nums;
std::vector<int> stack;

void solve(){
    
    if (stack.size() == M) {
        
        for (auto& el : stack) std::cout << el << ' ';
        std::cout << '\n';
        
        return;
    }
    
    for (int idx = cursor; idx < N; ++idx){
        
        cursor = idx;
        stack.push_back(nums[idx]);
        
        solve();
        
        stack.pop_back();
    }
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> nums[idx];
    std::sort(nums.begin(), nums.begin() + N);
    
    solve();
    
    return 0;
}


