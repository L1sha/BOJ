#include "bits/stdc++.h"


std::bitset<100> map;
char input;

void change(std::bitset<100>& map, int cursor) {
    
    map[cursor] = !map[cursor];
    
    if (cursor % 10 != 0) {
        
        map[cursor - 1] = !map[cursor - 1];
    }
    
    if (cursor % 10 != 9) {
        
        map[cursor + 1] = !map[cursor + 1];
    }
    
    if (cursor / 10 != 0) {
        
        map[cursor - 10] = !map[cursor - 10];
    }
    
    if (cursor / 10 != 9) {
        
        map[cursor + 10] = !map[cursor + 10];
    }
}

int solve(std::bitset<100> map, int bitMask) {
    
    int cursor = 0, cnt = 0;
    
    while (bitMask) {
        
        if (bitMask & 1) {
            
            change(map, cursor);
            cnt++;
        }
        
        bitMask >>= 1;
        cursor++;
    }
    
    for (int row = 1; row < 10; ++row) {
        
        for (int col = 0; col < 10; ++col) {
            
            if (map[(row - 1) * 10 + col]) {
                
                change(map, row * 10 + col);
                cnt++;
            }
        }
    }
    
    for (int idx = 90; idx < 100; ++idx) {
        
        if (map[idx]) {
            
            return INT_MAX;
        }
    }
    
    return cnt;
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    for (int idx = 0; idx < 100; ++idx) {
        
        std::cin >> input;
        
        if (input == 'O') {
            
            map[idx] = true;
        }
    }
    
    int res = INT_MAX;
    
    for (int bitMask = 0; bitMask < (1 << 10); ++bitMask) {
        
        res = std::min(res, solve(map, bitMask));
    }
    
    if (res == INT_MAX) {
        
        std::cout << -1;
    }
    else {
        
        std::cout << res;
    }
    
    return 0;
}

