#include "bits/stdc++.h"


int N, K;

std::array<int, 1'000'001> nums;


bool check(int divider){
    
    int res = 0;
    for (int idx = 0; idx < K; ++idx) res += nums[idx] / divider;
    return res >= N;
}


int solve(){
    
    long long left = 1, right = INT_MAX, mid;
    
    if (check(right)) return right;
    
    while (right - left > 1){
        
        mid = (left + right) / 2;
        
        if (check(mid)) left = mid;
        else right = mid;
    }
    
    return left;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> K >> N;
    
    for (int idx = 0; idx < K; ++idx) std::cin >> nums[idx];
    
    std::cout << solve();
    
    return 0;
}


