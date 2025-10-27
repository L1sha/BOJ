#include "bits/stdc++.h"


int N, K;
std::array<int, 100> nums;
std::array<int, 10001> res;




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    for (int idx = 0; idx < N; ++idx) std::cin >> nums[idx];
    
    res[0] = 1;
    for (int idx = 0; idx < N; ++idx) {
        
        for (int idx2 = nums[idx]; idx2 <= K; ++idx2) {
            
            res[idx2] += res[idx2 - nums[idx]];
        }
    }
    
    std::cout << res[K];
    
    return 0;
}

