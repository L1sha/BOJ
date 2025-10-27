#include "bits/stdc++.h"


constexpr int N_MAX = 10'000;

int N;
char C;
std::array<int, N_MAX> first, last;
std::array<std::array<std::optional<int>, 10>, N_MAX> memo;
std::array<std::array<int, 10>, N_MAX> res;

int solve(int cursor, int leftTurn) {
    
    if (cursor == N) {
        
        return 0;
    }
    
    if (memo[cursor][leftTurn].has_value()) {
        
        return memo[cursor][leftTurn].value();
    }
    
    int leftNeeded = (last[cursor] - first[cursor] - leftTurn + 20) % 10;
    int rightNeeded = (10 - leftNeeded) % 10;
    
    int left = leftNeeded + solve(cursor + 1, (leftTurn + leftNeeded) % 10);
    int right = rightNeeded + solve(cursor + 1, leftTurn);
    
    if (left < right) {
        
        res[cursor][leftTurn] = leftNeeded;
    }
    else {
        
        res[cursor][leftTurn] = -rightNeeded;
    }
    
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
    
    int leftTurn = 0;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cout << '\n' << idx + 1 << ' ' << res[idx][leftTurn];
        
        if (res[idx][leftTurn] > 0) {
            
            leftTurn = (leftTurn + res[idx][leftTurn]) % 10;
        }
    }
    
    return 0;
}

