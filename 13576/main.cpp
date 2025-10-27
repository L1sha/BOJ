#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N;
std::string S;

std::array<int, N_MAX> Z, suffixSum;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> S;
    N = S.length();
}

void makeZ() {
    
    Z[0] = N;
    suffixSum[N] = 1;
    
    int L = -1, R = -1;
    
    for (int idx = 1; idx < N; ++idx) {
        
        if (idx > R) {
            
            if (S[idx] == S[0]) {
                
                L = idx;
                R = idx;
                while (R + 1 < N && S[R - L + 1] == S[R + 1]) ++R;
                
                Z[idx] = R - L + 1;
            }
        }
        else {
            
            if (Z[idx - L] < R - idx + 1) Z[idx] = Z[idx - L];
            else if (Z[idx - L] > R - idx + 1) Z[idx] = R - idx + 1;
            else {  // Z[idx - L] == R - idx + 1
                
                // S[R - idx + 1] != S[R - L + 1]  <-  Z[idx - L] = R - idx + 1
                // S[R - L + 1] != S[R + 1]  <-  (L, R) 
                // then S[R - idx + 1] == S[R + 1] ?? 
                
                L = idx;
                while (R + 1 < N && S[R - L + 1] == S[R + 1]) ++R;
                
                Z[idx] = R - L + 1;
            }
        }
        
        ++suffixSum[Z[idx]];
    }
    
    for (int idx = N - 1; idx >= 1; --idx) suffixSum[idx] += suffixSum[idx + 1];
}

void solve() {
    
    makeZ();
    
    std::vector<std::pair<int, int>> res;
    res.reserve(N);
    
    for (int idx = N - 1; idx >= 0; --idx) {
        
        if (Z[idx] == N - idx) res.push_back({N - idx, suffixSum[N - idx]});
    }
    
    std::cout << res.size() << '\n';
    for (const auto& [L, C] : res) std::cout << L << ' ' << C << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}