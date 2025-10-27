#include "bits/stdc++.h"


int N;

std::array<std::array<int, 3>, 100'001> map;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < 3; ++idx2) std::cin >> map[idx][idx2];
    
    int max0 = map[0][0];
    int max1 = map[0][1];
    int max2 = map[0][2];
    
    int min0 = map[0][0];
    int min1 = map[0][1];
    int min2 = map[0][2];
    
    int temp1, temp2;
    
    for (int idx = 1; idx < N; ++idx){
        
        temp1 = std::max(max0, max1);
        temp2 = std::max(max1, max2);
        
        max0 = temp1 + map[idx][0];
        max1 = std::max(temp1, temp2) + map[idx][1];
        max2 = temp2 + map[idx][2];
        
        temp1 = std::min(min0, min1);
        temp2 = std::min(min1, min2);
        
        min0 = temp1 + map[idx][0];
        min1 = std::min(temp1, temp2) + map[idx][1];
        min2 = temp2 + map[idx][2];
    }
    
    std::cout << std::max(std::max(max0, max1), max2) << ' ' << std::min(std::min(min0, min1), min2);
    
    return 0;
}


