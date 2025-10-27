#include "bits/stdc++.h"


int N, X;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    std::vector<int> nums(N);
    for (auto& el : nums) std::cin >> el;
    std::sort(nums.begin(), nums.end());
    
    std::cin >> X;
    
    int cnt = 0, sum;
    auto left = nums.begin(), right = nums.end() - 1;
    
    while (left != right) {
        
        sum = *left + *right;
        
        if (sum > X) right--;
        else {
            
            if (sum == X) cnt++;
            left++;
        }
    }
    
    std::cout << cnt;
    
    return 0;
}

