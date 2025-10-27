#include "bits/stdc++.h"


int N, M;
std::array<int, 1'000'001> nums = {0, };




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    int temp;
    std::vector<int> cnt(M, 0);
    
    for (int idx = 0; idx < N; ++idx){
        
        std::cin >> temp;
        nums[idx + 1] = (nums[idx] + temp) % M;
        cnt[nums[idx + 1]]++;
    }
    
    int res = cnt[0];
    for (auto& el : cnt) res += el * (el - 1) / 2;
    
    std::cout << res;
    
    return 0;
}


