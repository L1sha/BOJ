#include "bits/stdc++.h"


int N;

std::array<int, 1'000'001> nums;
std::vector<int> sortedNums;
std::set<int> set;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    sortedNums.reserve(N);
    
    int temp;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> nums[idx]; 
        if (!set.count(nums[idx])) { set.insert(nums[idx]); sortedNums.push_back(nums[idx]); }
    }
    
    std::sort(sortedNums.begin(), sortedNums.end());
    
    for (int idx = 0; idx < N; ++idx) std::cout << std::distance(sortedNums.begin(), std::lower_bound(sortedNums.begin(), sortedNums.end(), nums[idx])) << ' ' ;
    
    
    return 0;
}



