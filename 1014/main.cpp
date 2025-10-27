#include "bits/stdc++.h"


// 1024 * 10 is possible. row by row

int C, N, M;
char input;

std::bitset<100> map;
std::array<std::array<int, 1024>, 100> memo;

void clear() {
    
    map.reset();
    
    for (auto& el : memo) {
        
        std::fill(el.begin(), el.end(), -1);
    }
}

std::bitset<100> fill(std::bitset<100> map, int cursor) {
    
    map[cursor] = false;
    
    if (cursor % M != 0) {
        
        map[cursor - 1] = false;
        
        if (cursor / M != N - 1) {
            
            map[cursor + M - 1] = false;
        }
    }
    
    if (cursor % M != M - 1) {
        
        map[cursor + 1] = false;
        
        if (cursor / M != N - 1) {
            
            map[cursor + M + 1] = false;
        }
    }
    
    return map;
}

int solve(std::bitset<100> map, int cursor) {
    
    if (cursor == N * M) {
        
        return 0;
    }
    
    while (!map[cursor]) {
        
        if (++cursor == N * M) {
            
            return 0;
        }
    }
    
    int bitMask = 0;
    
    for (int idx = 1; idx <= M; ++idx) {
        
        bitMask <<= 1;
        
        if (cursor + idx < N * M && map[cursor + idx]) {
            
            bitMask |= 1;
        }
    }
    
    if (memo[cursor][bitMask] != -1) {
        
        return memo[cursor][bitMask];
    }
    
    int max = 0;
    
    for (int toFill = cursor; toFill < N * M; ++toFill) {
        
        if (map[toFill]) {
            
            max = std::max(max, 1 + solve(fill(map, toFill), toFill + 1));
        }
    }
    
    return memo[cursor][bitMask] = max;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> C;
    
    while (C--) {
        
        clear();
        
        std::cin >> N >> M;
        
        for (int idx = 0; idx < N * M; ++idx) {
            
            std::cin >> input;
            
            if (input == '.') {
                
                map[idx] = true;
            }
        }
        
        std::cout << solve(map, 0) << '\n';
    }
    
    return 0;
}

