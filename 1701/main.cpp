#include "bits/stdc++.h"

std::string S;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> S;
}

int KMP(const int& startIdx) {
    
    int matched = 0;
    
    std::vector<int> pi(S.size() + 1);
    
    for (int idx = 2; idx <= S.size() - startIdx; ++idx) {
        
        if (S[startIdx + matched] == S[startIdx + idx - 1]) {
            
            pi[idx] = ++matched;
        }
        else if (matched) {
            
            matched = pi[matched];
            --idx;
        }
    }
    
    return *std::max_element(pi.begin(), pi.end());
}

void solve() {
    
    int res = 0;
    
    for (int idx = 0; idx < S.size(); ++idx) {
        
        res = std::max(res, KMP(idx));
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}