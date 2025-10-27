#include "bits/stdc++.h"

constexpr int N_MAX = 100'000, P_MAX = 3'000'001, fibo_MAX = 32;

int N;
std::array<int, P_MAX> grundyNumber;
std::array<int, N_MAX> P;
std::array<int, fibo_MAX> fibo;
std::bitset<fibo_MAX> nextGrundyNumber;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> P[idx];
}

void solve() {
    
    int maxIdx = 2;
    
    fibo[0] = 1;
    fibo[1] = 2;
    
    for (int idx = 2; idx < fibo_MAX; ++idx) fibo[idx] = fibo[idx - 1] + fibo[idx - 2];
    
    for (int idx = 1; idx < P_MAX; ++idx) {
        
        nextGrundyNumber.reset();
        
        for (int fiboIdx = 0; fiboIdx < fibo_MAX; ++fiboIdx) {
            
            if (idx - fibo[fiboIdx] >= 0) nextGrundyNumber[grundyNumber[idx - fibo[fiboIdx]]] = true;
            else break;
        }
        
        while (nextGrundyNumber[grundyNumber[idx]]) grundyNumber[idx]++;
    }
    
    int res = 0;
    
    for (int idx = 0; idx < N; ++idx) res ^= grundyNumber[P[idx]];
    
    if (res) std::cout << "koosaga";
    else std::cout << "cubelover";
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

