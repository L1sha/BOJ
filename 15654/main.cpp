#include "bits/stdc++.h"


int N, M, cursor = 0;

std::vector<int> nums;
std::vector<int> stack;
std::vector<bool> used;


void solve(){
    
    if (stack.size() == M){
        
        for (auto & el : stack) std::cout << el << ' ';
        std::cout << '\n';
        return;
    }
    
    for (int idx = 0; idx < N; ++idx) if (!used[idx]) {
        
        stack.push_back(nums[idx]);
        used[idx] = true;
        
        solve();
        
        used[idx] = false;
        stack.pop_back();
    }
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    nums.resize(N);
    used.resize(N, false);
    
    for (auto& el : nums) std::cin >> el;
    
    std::sort(nums.begin(),nums.end());
    
    solve();
    
    
    return 0;
}


