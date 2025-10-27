#include "bits/stdc++.h"


int N, K;
const int PRIME = 1'000'000'003;

std::array<std::array<int, 1001>, 501> memo;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    if (K > N / 2) {
        
        std::cout << 0;
        return 0;
    }
    
    std::fill(memo[0].begin(), memo[0].begin() + N + 1, 1);
    memo[1][1] = 1;
    
    for (int k = 1; k <= K; ++k) {
        
        for (int idx = 2; idx <= N; ++idx) {
            
            memo[k][idx] = (memo[k - 1][idx - 2] + memo[k][idx - 1]) % PRIME;
        }
    }
    
    if (K >= 2) std::cout << (memo[K][N] - memo[K - 2][N - 4] + PRIME) % PRIME;
    else std::cout << memo[K][N];
    
    return 0;
}

