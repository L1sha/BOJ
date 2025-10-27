#include "bits/stdc++.h"

constexpr long long N_MAX = 1e12;

long long N, A;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> A;
}

void solve() {
    
    std::cout << N - A << ' ';
    
    long long a1 = 1, b1 = 0, r1 = N,
        a2 = 0, b2 = 1, r2 = A,
        a3, b3, r3, q;
    
    while (r2) {
        
        q = r1 / r2;
        
        a3 = a1 - q * a2;
        b3 = b1 - q * b2;
        r3 = r1 - q * r2;
        
        a1 = a2, b1 = b2, r1 = r2;
        a2 = a3, b2 = b3, r2 = r3;
    }
    
    if (r1 != 1) std::cout << -1;
    else {
        
        while (b1 < 0) {
            
            b1 += N;
        }
        
        while (b1 > N) {
            
            b1 -= N;
        }
        
        std::cout << b1;
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}