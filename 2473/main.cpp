#include "bits/stdc++.h"


int N;

std::array<long long, 5001> nums;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> nums[idx];
    
    std::sort(nums.begin(), nums.begin() + N);
    
    std::array<int, 3> res;
    long long min = 1e10, temp;
    
    for (auto it = nums.begin(); it != nums.begin() + N; ++it){
        
        for (auto it2 = it + 1; it2 != nums.begin() + N; ++it2){
            
            auto it3 = std::lower_bound(it2 + 1, nums.begin() + N, -(*it) - (*it2));
           
            if (it3 != nums.begin() + N) {
                
                temp = (*it) + (*it2) + (*it3);
                if (temp < min) { 
                    
                    min = temp; 
                    res[0] = *it;
                    res[1] = *it2;
                    res[2] = *it3;
                }
            }
           
            if (it3 != it2 + 1) {
                
                temp = (*it) + (*it2) + (*(it3 - 1));
                temp = - temp;
                if (temp < min) { 
                    
                    min = temp; 
                    res[0] = *it;
                    res[1] = *it2;
                    res[2] = *(it3 - 1);
                }
            }
        }
    }
    
    std::cout << res[0] << ' ' << res[1] << ' ' << res[2];
    
    return 0;
}


