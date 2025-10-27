#include "bits/stdc++.h"

int N;

std::string S;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

bool get_input() {
    
    std::cin >> S;
    N = S.size();
    
    return S != ".";
}

void solve() {
    
    std::vector<int> pi(N + 1);
    
    int matched = 0;
    
    for (int idx = 2; idx <= N; ++idx) {
        
        if (S[idx - 1] == S[matched]) {
            
            pi[idx] = ++matched;
        }
        else if (matched) {
            
            matched = pi[matched];
            --idx;
        }
    }
    
    if (pi[N] && N % (N - pi[N]) == 0) std::cout << N / (N - pi[N]) << '\n';
    else std::cout << "1\n";
}



int main(int argc, char** argv) {
    
    fastIO();
    while (get_input()) solve();
    
    return 0;
}