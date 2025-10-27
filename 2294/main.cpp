#include "bits/stdc++.h"


int N, K;

std::vector<int> coins;
std::array<int, 10'001> res;

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K;
    
    coins.reserve(N);
    
    int input;
    while (N--) {
        
        std::cin >> input;
        if (input <= K && res[input] == 0) {
            
            res[input] = 1;
            coins.push_back(input);
        }
    }
}

void solve() {
    
    for (int idx = 0; idx < K; ++idx) {
        
        if (res[idx]) {
            
            for (const auto& coin : coins) {
                
                if (idx + coin <= K) {
                    
                    if (res[idx + coin]) res[idx + coin] = std::min(res[idx + coin], res[idx] + 1);
                    else res[idx + coin] = res[idx] + 1;
                }
            }
        }
    }
    
    if (res[K]) std::cout << res[K];
    else std::cout << -1;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

