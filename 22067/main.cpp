#include "bits/stdc++.h"

constexpr int N_MAX = 300;

int N;

std::array<std::bitset<N_MAX + 1>, N_MAX + 1> adjM;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int from, to, idx = 0; idx < N - 1; ++idx) {
        
        std::cin >> from >> to;
        adjM[from][to] = true;
        adjM[to][from] = true;
    }
    
    for (int idx = 1; idx <= N; ++idx) adjM[idx][idx] = true;
}

void solve() {
    
    if (N <= 4) {    
        
        if (N == 2) std::cout << 0 << '\n' << 1;
        else if (N == 3) std::cout << 1 << '\n' << 1 << '\n';
        else if (N == 4) std::cout << 3 << '\n' << 1 << '\n';
        
        for (int from = 1; from <= N; ++from) {
            
            for (int to = 1; to <= N; ++to) {
                
                if (!adjM[from][to]) {
                    
                    std::cout << from << ' ' << to << '\n';
                    adjM[from][to] = true;
                    adjM[to][from] = true;
                }
            }
        }
    }
    else {
        
        int maxCnt = 0, maxIdx = 0;
        
        for (int from = 1; from <= N; ++from) {
            
            int cnt = 0;
            
            for (int to = 1; to <= N; ++to) {
                
                if (adjM[from][to]) ++cnt;
            }
            
            if (cnt > maxCnt) {
                
                maxCnt = cnt;
                maxIdx = from;
            }
        }
        
        std::cout << N - maxCnt << '\n' << 2 << '\n';
        
        for (int to = 1; to <= N; ++to) {
            
            if (!adjM[maxIdx][to]) {
                
                std::cout << maxIdx << ' ' << to << '\n';
            }
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}