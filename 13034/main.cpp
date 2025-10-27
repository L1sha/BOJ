#include "bits/stdc++.h"

constexpr int N_MAX = 1001;

int N;

std::array<int, N_MAX> grundyNumber;
std::bitset<N_MAX> nextGrundyNumber;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
}

void solve() {
    
    for (int idx = 2; idx <= N; ++idx) {
        
        nextGrundyNumber.reset();
        
        for (int left = 0; left <= (idx - 2) / 2; ++left) {
            
            nextGrundyNumber[grundyNumber[left] ^ grundyNumber[idx - 2 - left]] = true;
        }
        
        while (nextGrundyNumber[grundyNumber[idx]]) grundyNumber[idx]++;
    }
    
    if (grundyNumber[N]) std::cout << 1;
    else std::cout << 2;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

