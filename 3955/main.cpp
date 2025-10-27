#include "bits/stdc++.h"

constexpr int KC_MAX = 1e9;

long long K, C;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> K >> C;
}

void solve() {
    
    long long a1 = 1, b1 = 0, r1 = K,
        a2 = 0, b2 = 1, r2 = C,
        a3, b3, r3, q;
    
    if (K < C) {
        
        std::swap(a1, a2);
        std::swap(b1, b2);
        std::swap(r1, r2);
    }
    
    while (r2) {
        
        q = r1 / r2;
        
        a3 = a1 - q * a2;
        b3 = b1 - q * b2;
        r3 = r1 - q * r2;
        
        a1 = a2, b1 = b2, r1 = r2;
        a2 = a3, b2 = b3, r2 = r3;
    }
    
    if (r1 != 1) std::cout << "IMPOSSIBLE\n";
    else {
        
        while (a1 >= 0 || b1 <= 0) {
            
            a1 -= C;
            b1 += K;
        }
        
        if (b1 > 1'000'000'000) std::cout << "IMPOSSIBLE\n";
        else std::cout << b1 << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    int T; std::cin >> T;
    while (T--) {
        
        get_input();
        solve();
    }
    
    return 0;
}