#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N;
std::stack<intPair> s;
std::array<int, 1'000'001> res;
std::array<int, 1'000'001> nums;
std::unordered_map<int, int> F;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    std::fill(res.begin(), res.begin() + N, -1);
    
    intPair top;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> nums[idx];
        
        if (F.count(nums[idx])) F[nums[idx]]++;
        else F[nums[idx]] = 1;
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        while (!s.empty() && F[(top = s.top()).first] < F[nums[idx]]) {
            
            s.pop();
            res[top.second] = nums[idx];
        }
        
        s.push({nums[idx], idx});
    }

    for (int idx = 0; idx < N; ++idx) std::cout << res[idx] << ' ' ;
    
    return 0;
}

