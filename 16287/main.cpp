#include "bits/stdc++.h"


int W, N;

constexpr int MAXSIZE = 5000 * 4999 / 2;

std::array<int, 5000> nums;
std::array<std::tuple<int, int, int>, MAXSIZE> twoNums;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> W >> N;
    
    int temp, cursor = 0;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> nums[idx];
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        for (int idx2 = idx + 1; idx2 < N; ++idx2) {
            
            twoNums[cursor++] = {nums[idx] + nums[idx2], idx, idx2};
        }
    }
    
    sort(twoNums.begin(), twoNums.begin() + cursor);
    
    int left = 0, right = cursor - 1, sum;
    
    while (left < right) {
        
        sum = std::get<0>(twoNums[left]) + std::get<0>(twoNums[right]);
        
        if (sum > W) {
            
            right--;
        }
        else {
            
            if (sum == W) {
                
                int a = std::get<1>(twoNums[left]), b = std::get<2>(twoNums[left]);
                int c = std::get<1>(twoNums[right]), d = std::get<2>(twoNums[right]);
                
                if (a != c && a != d && b != c  && b != d) {
                    
                    std::cout << "YES";
                    return 0;
                }
            }
            
            left++;
        }
    }
    
    std::cout << "NO";
    return 0;
}

