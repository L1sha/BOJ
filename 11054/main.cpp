#include "bits/stdc++.h"


int N;
std::array<int, 1001> nums;
std::array<int, 1001> inc;
std::array<int, 1001> dec;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> nums[idx];
    
    for (int idx = 0; idx < N; ++idx){
        
        inc[idx] = 1;
        dec[N - idx - 1] = 1;
        
        for (int idx2 = 0; idx2 < idx; ++idx2) {
            
            if (inc[idx2] >= inc[idx] && nums[idx] > nums[idx2]) inc[idx] = inc[idx2] + 1;
            
            if (dec[N - 1 - idx2] >= dec[N - 1 - idx] && nums[N - 1 - idx] > nums[N - 1 - idx2]) dec[N - 1 - idx] = dec[N - 1 - idx2] + 1;
        }
    }
    
    for (int idx = 0; idx < N; ++idx) nums[idx] = inc[idx] + dec[idx] - 1;
    
    std::cout << *std::max_element(nums.begin(), nums.begin() + N);
    
    return 0;
}


