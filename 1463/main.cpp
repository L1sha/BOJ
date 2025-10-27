#include "bits/stdc++.h"


int N;

std::array<std::optional<int>, 1'000'001> memo;

int minOperation(int N){
    
    if (memo[N].has_value()) return memo[N].value();
    
    if (N % 3 != 0){
        
        if (N % 2 != 0) memo[N] = minOperation(N - 1) + 1;
        else memo[N] = std::min(minOperation(N - 1) + 1, minOperation(N / 2) + 1);
    } 
    else {
        
        if (N % 2 != 0) memo[N] = std::min(minOperation(N - 1) + 1, minOperation(N / 3) + 1);
        else memo[N] = std::min(std::min(minOperation(N - 1) + 1, minOperation(N / 2) + 1), minOperation(N / 3) + 1);
    }
    
    return memo[N].value();
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    memo[1] = 0;
    memo[2] = 1;
    memo[3] = 1;
    
    std::cout << minOperation(N);
    
    return 0;
}


