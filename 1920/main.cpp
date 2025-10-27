#include "bits/stdc++.h"


int N, M;

std::array<int, 100'001> nums;

int check(const int& checker){
    
    int left = 0, right = N - 1, mid;
    
    if (nums[left] > checker || nums[right] < checker) return 0;
    if (nums[left] == checker || nums[right] == checker) return 1;
    
    while (right - left > 1){
        
        mid = (left + right) / 2;
        if (nums[mid] == checker) return 1;
        else if (nums[mid] > checker) right = mid;
        else left = mid;
    }
    
    return 0;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    
    std::cin >> N;
        
    for (int idx = 0; idx < N; ++idx) std::cin >> nums[idx];
    std::sort(nums.begin(), nums.begin() + N);
        
    std::cin >> M;
    
    int checker;
    
    while(M--){
        
        std::cin >> checker;
        std::cout << check(checker) << '\n';
    }
    
    return 0;
}


