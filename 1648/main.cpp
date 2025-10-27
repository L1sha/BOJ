#include "bits/stdc++.h"


constexpr int N_MAX = 14, M_MAX = 14, bit_MAX = 16384;
const int PRIME = 9901;

int N, M;

std::array<std::array<std::optional<int>, bit_MAX>, N_MAX> memo;

int solve(int row, std::bitset<M_MAX> filled);

void fill(const int& row, int cursor, const std::bitset<M_MAX>& filled, std::bitset<M_MAX>& next, int& ans) {
    
    while (cursor < M && filled[cursor]) {
        
        cursor++;
    }
    
    if (cursor == M) {
        
        ans = (ans + solve(row + 1, next)) % PRIME;
    }
    else {
        
        if (cursor != M - 1 && !filled[cursor + 1]) {
            
            fill(row, cursor + 2, filled, next, ans);
        }
        
        next[cursor] = true;
        
        fill(row, cursor + 1, filled, next, ans);
        
        next[cursor] = false;
    }
}

int solve(int row, std::bitset<M_MAX> filled) {
    
    int bitMask = filled.to_ulong();
    
    if (memo[row][bitMask].has_value()) {
        
        return memo[row][bitMask].value();
    }
    
    if (row == N - 1) {
        
        for (int col = 0; col < M; ++col) {
            
            if (!filled[col]) {
                
                if (col == M - 1 || filled[col + 1]) {
                    
                    return (memo[row][bitMask] = 0).value();
                }
                
                col++;
            }
        }
        
        return (memo[row][bitMask] = 1).value();
    }
    
    int ans = 0;
    std::bitset<M_MAX> next;
    
    fill(row, 0, filled, next, ans);
    
    return (memo[row][bitMask] = ans).value();
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    std::cout << solve(0, std::bitset<M_MAX>());
    
    return 0;
}

