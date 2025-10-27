#include "bits/stdc++.h"


int N, M, K;
std::vector<int> nums;
std::array<int, 4'000'000> parent;

int getParent(int idx){
    
    if (parent[idx] != idx) return parent[idx] = getParent(parent[idx]);
    return idx;
}

void Union(int idx1, int idx2) {
    
    parent[getParent(idx1)] = getParent(idx2);
}


int solve(int input) {
    
    int idx = std::distance(nums.begin(), std::lower_bound(nums.begin(), nums.end(), input));
    if (nums[idx] == input) idx++;
    
    int p = getParent(idx), res = nums[p];
    
    if (p != M - 1) Union(p, p + 1);
    
    return res;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> K;
    nums.resize(M);
    for (auto& el : nums) std::cin >> el;
    
    std::sort(nums.begin(), nums.end());
    
    for (int idx = 0; idx < M; ++idx) parent[idx] = idx;
    
    int input;
    while (K--) {
        
        std::cin >> input;
        std::cout << solve(input) << '\n';
    }
    
    
    return 0;
}

