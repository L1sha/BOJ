#include "bits/stdc++.h"


int N, T;

std::array<int, 11> memo;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    memo[1] = 1;
    memo[2] = 2;
    memo[3] = 4;
    for (int idx = 4; idx < 11; ++idx) memo[idx] = memo[idx - 1] + memo[idx - 2] + memo[idx - 3];
    
    while (T--) { std::cin >> N; std::cout << memo[N] << '\n'; }
    
    return 0;
}


