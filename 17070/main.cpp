#include "bits/stdc++.h"

const int horizontal = 0, diagonal = 1, vertical = 2;
using intPair = std::pair<int, int>;

int N;
std::array<std::array<int, 17>, 17> map;
std::array<std::array<std::array<std::optional<int>, 3>, 17>, 17> memo;

int solve(int X, int Y, int state){
    
    if (memo[X][Y][state].has_value()) return memo[X][Y][state].value();
    
    int res = 0;
    
    switch (state) {
        
        case horizontal:
        
        if (X == N - 1) {
            
            if (Y == N){
            
                memo[X][Y][state] = 1;
                return 1;
            }
            else {
                
                memo[X][Y][state] = 0;
                return 0;
            }
        }
        
        if (!map[X + 2][Y]) res += solve(X + 1, Y, horizontal);
        if (Y != N) if (!map[X + 2][Y + 1] && !map[X + 1][Y + 1] && !map[X + 2][Y]) res += solve(X + 1, Y, diagonal);
        
        break;
        
        case diagonal:
        
        if (X == N - 1 && Y == N - 1) {
            
            memo[X][Y][state] = 1;
            return 1;
        }
        
        if (Y != N - 1) if (!map[X + 1][Y + 2]) res += solve(X + 1, Y + 1, vertical);
        if (X != N - 1) if (!map[X + 2][Y + 1]) res += solve(X + 1, Y + 1, horizontal);
        if (X != N - 1 && Y != N - 1) if (!map[X + 2][Y + 2] && !map[X + 1][Y + 2] && !map[X + 2][Y + 1]) res += solve(X + 1, Y + 1, diagonal);
        
        break;
        
        case vertical:
        
        if (Y == N - 1) {
            
            if (X == N){
            
                memo[X][Y][state] = 1;
                return 1;
            }
            else {
                
                memo[X][Y][state] = 0;
                return 0;
            }
        }
        
        if (!map[X][Y + 2]) res += solve(X, Y + 1, vertical);
        if (X != N) if (!map[X + 1][Y + 2] && !map[X + 1][Y + 1] && !map[X][Y + 2]) res += solve(X, Y + 1, diagonal);
        
        break;
    }
    
    memo[X][Y][state] = res;
    return res;
}




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) for (int idx2 = 1; idx2 <= N; ++idx2) std::cin >> map[idx2][idx];
    
    std::cout << solve(1, 1, horizontal);
    
    return 0;
}





