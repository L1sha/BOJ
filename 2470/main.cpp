#include "bits/stdc++.h"


int N;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    std::vector<int> nums(N);
    for (auto& el : nums) std::cin >> el;
    std::sort(nums.begin(), nums.end());
    
    auto left = nums.begin(), right = nums.end() - 1;
    std::pair<int, int> res;
    int min = 2e9 + 1, sum;
    
    while (left != right) {
        
        sum = *left + *right;
        
        if (std::abs(sum) < min) {
            
            min = std::abs(sum);
            res = {*left, *right};
            if (min == 0) break;
        }
        
        if (sum < 0) left++;
        else right--;
    }
    
    std::cout << res.first << ' ' << res.second;
    
    return 0;
}

