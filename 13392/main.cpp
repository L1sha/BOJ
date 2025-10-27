#include "bits/stdc++.h"


constexpr int N_MAX = 10'000;

int N;
char C;
std::array<int, N_MAX> first, last;
std::array<std::array<std::optional<int>, 10>, N_MAX> memo;

int solve(int cursor, int leftTurn) {
    
    if (cursor == N) {
        
        return 0;
    }
    
    if (memo[cursor][leftTurn].has_value()) {
        
        return memo[cursor][leftTurn].value();
    }
    
    int left = (last[cursor] - first[cursor] - leftTurn + 20) % 10;
    int right = (10 - left) % 10;
    
    left = left + solve(cursor + 1, (leftTurn + left) % 10);
    right = right + solve(cursor + 1, leftTurn);
    
    return (memo[cursor][leftTurn] = std::min(left, right)).value();
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> C;
        first[idx] = C - '0';
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> C;
        last[idx] = C - '0';
    }
    
    std::cout << solve(0, 0);
    
    return 0;
}

