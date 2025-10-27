#include "bits/stdc++.h"


int N, res = 1e9, temp = 0;

std::array<std::array<int, 16>, 16> adjM;
std::array<std::array<std::array<std::optional<int>, (1 << 14)>, 16>, 16> memo;

int solve(int from, int to, int bitMask){
    
    if (memo[from][to][bitMask].has_value()) return memo[from][to][bitMask].value();
    
    if (!bitMask) {
        
        if (!adjM[from][to]) {
            
            memo[from][to][bitMask] = -1;
            return -1;
        }
        else {
            
            memo[from][to][bitMask] = adjM[from][to];
            return adjM[from][to];
        }
    }
    
    int cnt = 0, temp = bitMask;
    std::vector<int> cities;
    
    while (temp) {
        
        if (temp % 2) cities.push_back(cnt);
        cnt++;
        temp >>= 1;
    }
    
    int res = 1e9;
    
    bitMask &= ~(1 << cities[0]);
    int newBitMask, left, right;
    
    for (int idx = 0; idx < (1 << (cities.size() - 1)); ++idx){
        
        newBitMask = 0;
        cnt = 1;
        temp = idx;
        
        while (temp) {
            
            if (temp % 2) newBitMask |= (1 << cities[cnt]);
            cnt++;
            temp >>= 1;
        }
        
        left = solve(from, cities[0], newBitMask);
        right = solve(cities[0], to, bitMask - newBitMask);
        
        if (left != -1 && right != -1) res = std::min(res, left + right);
    }
    
    bitMask |= (1 << cities[0]);
    
    if (res == 1e9) {
        
        memo[from][to][bitMask] = -1;
        return -1;
    }
    
    memo[from][to][bitMask] = res;
    return res;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < N; ++idx2) std::cin >> adjM[idx][idx2];
    
    int res = 1e9, left, right;
    
    for (int idx = 0; idx < (1 << (N - 2)); ++idx){
        
        left = solve(N - 1, N - 2, idx);
        right = solve(N - 2, N - 1, (1 << (N - 2)) - 1 - idx);
        if (left != -1 && right != -1) res = std::min(res, left + right);
    }
    
    std::cout << res;
    
    return 0;
}



