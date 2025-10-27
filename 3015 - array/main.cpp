#include "bits/stdc++.h"


int N;

std::array<int, 500'000> nums;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    int temp, length = 0, dist;
    long long cnt = 0;
    
    while (N--) {
        
        std::cin >> temp;
        temp = -temp;
        
        if (length) {
            
            dist = std::distance(nums.begin(), std::upper_bound(nums.begin(), nums.begin() + length, temp));
            cnt += (length - dist);
            length = dist;
        }
        if (length) { 
        
            if (nums[length - 1] == temp) {
            
                auto itpair = std::equal_range(nums.begin(), nums.begin() + length, temp);
                dist = std::distance(itpair.first, itpair.second);
                cnt += dist;
                
                if (dist != length) cnt++;
            }
            else cnt++;
        }
        nums[length++] = temp;
    }
    
    std::cout << cnt;
    
    return 0;
}

