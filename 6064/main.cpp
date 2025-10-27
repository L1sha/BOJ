#include "bits/stdc++.h"

int M, N, x, y, T;

int GCD(int a, int b) {
    
    if (a == 0) return b;
    return GCD(b % a, a);
}

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void solve() {
    
    std::cin >> T;
    
    int G, L;
    
    while (T--) {
        
        std::cin >> M >> N >> x >> y;
        
        if (M > N) {
            
            std::swap(M, N);
            std::swap(x, y);
        }
        
        G = GCD(M, N);
        L = M / G * N;
        
        --x;
        --y;
        
        int res = x;
        
        while (res % N != y && res < L) {
            
            res += M;
        }
        
        if (res >= L) std::cout << -1 << '\n';
        else std::cout << res + 1 << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    solve();
    
    return 0;
}

