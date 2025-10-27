#include "bits/stdc++.h"


int N;
std::array<std::array<int, 20>, 20> D;
std::array<int, 1 << 20> memo;

int solve(int bitMask){
    
    if (memo[bitMask]) return memo[bitMask];
    if (bitMask == 0) return 0;
    
    int temp = bitMask, cursor = 0, cnt;
    std::vector<int> candidates;
    
    while (temp) {
        
        if (temp % 2) {
            
            candidates.push_back(cursor);
        }
        
        cursor++;
        temp /= 2;
    }
    
    cnt = candidates.size();
    temp = INT_MAX;
    
    for (auto& el : candidates) {
        
        temp = std::min(temp, D[el][cnt - 1] + solve(bitMask & ~(1 << el)));
    }
    
    memo[bitMask] = temp;
    return temp;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < N; ++col) {
            
            std::cin >> D[row][col];
        }
    }
    
    std::cout << solve((1 << N) - 1);
    
    return 0;
}

