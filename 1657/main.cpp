#include "bits/stdc++.h"


constexpr int N_MAX = 14, M_MAX = 14, bit_MAX = 16384;

int N, M;
char C;

std::array<std::array<int, M_MAX>, N_MAX> map;
std::array<std::array<int, 5>, 5> score;
std::array<std::array<std::optional<int>, bit_MAX>, N_MAX> memo;

int solve(int, std::bitset<M_MAX>);

void fill(const int& row, int cursor, std::bitset<M_MAX>& filled, std::bitset<M_MAX>& next, int& ans, int& rowScore) {
    
    while (cursor < M && filled[cursor]) {
        
        cursor++;
    }
    
    if (cursor == M) {
        
        ans = std::max(ans, rowScore + solve(row + 1, next));
    }
    else {
        
        if (cursor == 0 || filled[cursor - 1]) {
            
            fill(row, cursor + 1, filled, next, ans, rowScore);
        }
        
        if (cursor != M - 1 && !filled[cursor + 1]) {
            
            filled[cursor + 1] = true;
            rowScore += score[map[row][cursor]][map[row][cursor + 1]];
            
            fill(row, cursor + 2, filled, next, ans, rowScore);
            
            filled[cursor + 1] = false;
            rowScore -= score[map[row][cursor]][map[row][cursor + 1]];
        }
        
        if (row != N - 1) {
            
            filled[cursor] = true;
            next[cursor] = true;
            rowScore += score[map[row][cursor]][map[row + 1][cursor]];
            
            fill(row, cursor + 1, filled, next, ans, rowScore);
            
            filled[cursor] = false;
            next[cursor] = false;
            rowScore -= score[map[row][cursor]][map[row + 1][cursor]];
        }
    }
}

int solve(int row = 0, std::bitset<M_MAX> filled = {}) {
    
    if (row == N) {
        
        return 0;
    }
    
    int bitMask = filled.to_ulong();
    
    if (memo[row][bitMask].has_value()) {
        
        return memo[row][bitMask].value();
    }
    
    int ans = 0, rowScore = 0;
    std::bitset<M_MAX> next;
    
    fill(row, 0, filled, next, ans, rowScore);
    
    return (memo[row][bitMask] = ans).value();
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    score[0] = {10, 8, 7, 5, 1};
    score[1] = {8, 6, 4, 3, 1};
    score[2] = {7, 4, 3, 2, 1};
    score[3] = {5, 3, 2, 2, 1};
    score[4] = {1, 1, 1, 1, 0};
    
    std::cin >> N >> M;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            std::cin >> C;
            
            map[row][col] = C - 'A';
            
            if (C == 'F') {
                
                map[row][col]--;
            }
        }
    }
    
    std::cout << solve();
    
    return 0;
}