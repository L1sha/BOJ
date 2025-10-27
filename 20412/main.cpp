#include "bits/stdc++.h"

constexpr long long M_MAX = 1'000'000'000;

long long M, Seed, X1, X2;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> M >> Seed >> X1 >> X2;
}

void solve() {
    
    if (Seed == X1) {
        
        std::cout << 0 << ' ' << Seed;
        return;
    }
    
    // pa = q (mod M)
    long long a, c, p = (Seed - X1 + M) % M, q = (X1 - X2 + M) % M;
    
    // find inverse(p)
    long inv = 1;
    
    for (long long power = M - 2, temp = p; power; power >>= 1) {
        
        if (power & 1) inv = (inv * temp) % M;
        temp = (temp * temp) % M;
    }
    
    a = (q * inv) % M;
    c = (X1 - (a * Seed) % M + M) % M;
    
    std::cout << a << ' ' << c;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}