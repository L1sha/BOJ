#include "bits/stdc++.h"


int N;

std::array<int, 1001> max;
std::array<int, 1001> num;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx){
        
        std::cin >> num[idx];
        
        max[idx] = 1;
        for (int idx2 = 1; idx2 < N; ++idx2) if (max[idx2] >= max[idx] && num[idx] > num[idx2]) max[idx] = max[idx2] + 1;
    }
    
    std::cout << *std::max_element(max.begin(), max.begin() + N + 1);
    
    return 0;
}


