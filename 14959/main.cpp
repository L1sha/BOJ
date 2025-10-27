#include "bits/stdc++.h"

constexpr int N_MAX = 1'000'001;

int N;

using intPair = std::pair<int, int>;

std::array<int, N_MAX> revT, KMP;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int idx = N - 1; idx >= 0; --idx) std::cin >> revT[idx];
}

void solve() {
    
    for (int corrected = 0, idx = 2; idx <= N; ++idx) {
        
        if (revT[corrected] == revT[idx - 1]) KMP[idx] = ++corrected;
        else if (corrected > 0) {
            
            corrected = KMP[corrected];
            idx--;
        }
    }
    
    int K = N - 1, P = 1;
    
    for (int prev = -1, idx = 2; idx <= N; ++idx) {
        
        if (KMP[idx]) {
            
            int newK = N - idx;
            int newP = idx - KMP[idx];
            
            if (newK + newP < K + P || (newK + newP == K + P && newP < P)) {
                
                K = newK;
                P = newP;
            }
        }
    }
    
    std::cout << K << ' ' << P;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

