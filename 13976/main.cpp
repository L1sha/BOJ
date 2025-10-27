#include "bits/stdc++.h"

/*

f(n) = f(n - 2) + 2g(n - 1)
g(n) = f(n - 1) + g(n - 2)

=> f(n + 1) - f(n - 1) = 2f(n - 1) + f(n - 1) - f(n - 3)
f(n + 1) = 4f(n - 1) - f(n - 3)
f(n + 4) = 4f(n + 2) - f(n), f(0) = 1, f(2) = 3

n = 2k, f'(k) = f(2k) -> f'(k + 2) = 4f'(k + 1) - f'(k), f'(0) = 1, f'(1) = 3

A = 2 - sqrt(3), B = 2 + sqrt(3)
f'(k + 2) - Af'(k + 1) = B (f'(k + 1) - Af'(k))
-> f'(k + 1) - Af'(k) = B^k (f'(1) - Af'(0)) = (2 + sqrt(3))^k (1 + sqrt(3))

Let (2 + sqrt(3))^k = C(k) + D(k) sqrt(3), where C(k) & D(k) : natural number

{f'(k + 1) - 2f'(k)} + {f'(k)}sqrt(3) = (C(k) + D(k)sqrt(3))(1 + sqrt(3))
= (C(k) + 3D(k)) + (C(k) + D(k))sqrt(3)

=> f'(k) = C(k) + D(k)

*/

long long N;

const int PRIME = 1'000'000'007;

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    if (N & 1) {
        
        std::cout << 0;
        
        return 0;
    }
    
    N >>= 1;
    
    long long C = 1, D = 0, Cpow = 2, Dpow = 1, newC, newD;
    
    while (N) {
        
        if (N & 1) {
            
            newC = (C * Cpow + 3 * D * Dpow) % PRIME;
            newD = (C * Dpow + D * Cpow) % PRIME;
            
            C = newC;
            D = newD;
        }
        
        newC = (Cpow * Cpow + 3 * Dpow * Dpow) % PRIME;
        newD = (Cpow * Dpow + Dpow * Cpow) % PRIME;
        
        Cpow = newC;
        Dpow = newD;
        
        N >>= 1;
    }
    
    std::cout << (C + D) % PRIME;
    
    return 0;
}


