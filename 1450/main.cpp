#include "bits/stdc++.h"


int N, C;

std::array<int, 30> nums;
std::array<long long, 32768> small;
std::array<long long, 32768> large;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> C;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> nums[idx];
    std::sort(nums.begin(), nums.begin() + N);
    
    int bitmask, cursor, smallSize = (1 << (N / 2)), largeSize = (1 << (N - N / 2));
    
    for (int idx = 0; idx < smallSize; ++idx) {
        
        bitmask = idx;
        cursor = 0;
        
        while (bitmask) {
            
            small[idx] += (bitmask % 2) * nums[cursor];
            
            bitmask /= 2;
            cursor++;
        }
    }
    
    std::sort(small.begin(), small.begin() + smallSize);
    
    for (int idx = 0; idx < largeSize; ++idx) {
        
        bitmask = idx;
        cursor = N / 2;
        
        while (bitmask) {
            
            large[idx] += (bitmask % 2) * nums[cursor];
            
            bitmask /= 2;
            cursor++;
        }
    }
    
    std::sort(large.begin(), large.begin() + largeSize);
    
    int left = 0, right = largeSize - 1, sum, cnt = 0;
    
    while (left < smallSize && right >= 0) {
        
        if (small[left] + large[right] <= C) {
            
            cnt += (right + 1);
            left++;
        }
        else {
            
            right--;
        }
    }
    
    std::cout << cnt;
    
    return 0;
}

