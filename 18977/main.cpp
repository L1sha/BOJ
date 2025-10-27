#include "bits/stdc++.h"

int T, N;

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> T;
}

void solve() {
    
    while (T--) {
        
        std::cin >> N;
        
        if (N % 3 == 0) {
            
            long long res = N / 3;
            res *= N / 3;
            res *= N / 3;
            
            std::cout << res << '\n';
        }
        else if (N % 4 == 0) {
            
            long long res = N / 2;
            res *= N / 4;
            res *= N / 4;
            
            std::cout << res << '\n';
        }
        else {
            
            std::cout << -1 << '\n';
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

