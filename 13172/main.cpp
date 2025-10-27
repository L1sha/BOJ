#include "bits/stdc++.h"


int M;
long long N, S;

long long res;
const long long PRIME = 1'000'000'007;

long long power(long long base, int exponent) {
    
    long long res = 1;
    
    while (exponent) {
        
        if (exponent % 2) res = (res * base) % PRIME;
        base = (base * base) % PRIME;
        exponent /= 2;
    }
    
    return res;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> N >> S;
        
        res = (res + (S * power(N, PRIME - 2))) % PRIME;
    }
    
    std::cout << res;
    
    return 0;
}


