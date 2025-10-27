#include "bits/stdc++.h"


int N, M, K;
const int PRIME = 1'000'000'007;
std::array<long long, 4'000'001> factorial;


void fact() {
    
    factorial[0] = 1;
    for (int idx = 1; idx <= 4'000'000; ++idx) {
        
        factorial[idx] = (factorial[idx - 1] * idx) % PRIME;
    }
}

long long power(long long base, int expo = PRIME - 2) {
    
    long long res = 1;
    base %= PRIME;
    
    while (expo) {
        
        if (expo % 2) {
            
            res = (res * base) % PRIME;
        }
        
        expo /= 2;
        base = (base * base) % PRIME;
    }
    
    return res;
}

long long nCk() {
    
    return (factorial[N] * power(factorial[K] * factorial[N - K])) % PRIME;
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    fact();
    
    std::cin >> M; 
    
    while (M--) {
        
        std::cin >> N >> K;
        std::cout << nCk() << '\n';
    }
    
    return 0;
}

