#include "bits/stdc++.h"


/*

Fermat's little theorem
a^p = a (mod p)
(a, p) = 1 -> a^(p-1) = 1 (mod p)

=> b / a = b / a * a^(p - 1) = b * a^(p - 2) (mod p)

*/


int N, K;
long long num = 1, denom = 1;

const int PRIME = 1'000'000'007;



long long power(int base, int exponent){
    
    long long res = 1, temp = base % PRIME;
    
    while (exponent != 0){
        
        if (exponent % 2 == 1) res = (res * temp) % PRIME;
        
        temp = (temp * temp) % PRIME;
        exponent /= 2;
    }
    
    return res;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        num = (num * idx) % PRIME;
        if (idx == K || idx == N - K) denom = (denom * num) % PRIME;
    }
    if (K * 2 == N) denom = (denom * denom) % PRIME;
    
    std::cout << (num * power(denom, PRIME - 2)) % PRIME;
    
    return 0;
}



