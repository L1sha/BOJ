#include "bits/stdc++.h"


int N, S;

std::array<int, 100'001> nums;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> S;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> nums[idx];
    
    int res = 1e9;
    
    int left = 0, right = 0, sum = 0;
    
    while (right < N || sum >= S){
        
        if (sum < S) sum += nums[right++];
        else {
            
            res = std::min(res, right - left);
            sum -= nums[left++];
        }
    }
    
    if (res == 1e9) res = 0;
    
    std::cout << res;
    
    return 0;
}


