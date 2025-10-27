#include "bits/stdc++.h"

constexpr int N_MAX = 51, S_MAX = 1001;

int N, S;

std::array<std::array<bool, S_MAX>, N_MAX> visited;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> S;
}

bool getDP(int N, int S) {
    
    if (visited[N][S]) return false;
    
    if (N <= 0) {
        
        if (S == 0) return true;
        else return false;
    }
    else if (S == 0) return false;
    
    for (int next = N; next > 0; --next) {
        
        if (S >= (next + 1) * next / 2) {
            
            if (getDP(N - next, S - (next + 1) * next / 2)) return true;
        }
    }
    
    visited[N][S] = true;
    return false;
}

void solve() {
    
    if (getDP(N - 2, S)) std::cout << 1;
    else std::cout << 0;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}