#include "bits/stdc++.h"

constexpr int N_MAX = 1'000'000;

int N, M;

std::string S;

std::array<int, N_MAX> Z;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> S >> M;
    N = S.length();
}

void solve() {
    
    std::reverse(S.begin(), S.end());
    
    int L = 0, R = 0;
    
    Z[0] = N;
    
    for (int idx = 1; idx < N; ++idx) {
        
        if (R < idx) {
            
            if (S[0] == S[idx]) {
                
                ++Z[idx];
                L = idx;
                R = idx;
                
                while (R + 1 < N && S[R - L + 1] == S[R + 1]) {
                    
                    ++Z[idx];
                    ++R;
                }
            }
        }
        else {  // L <= idx <= R
            
            // S[(idx - L) ~ (R - L)] = S[idx ~ R] => check Z[idx - L]
            if (Z[idx - L] < R - idx + 1) {
                
                Z[idx] = Z[idx - L];
            }
            else {
                
                Z[idx] = R - idx + 1;
                L = idx;
                
                while (R + 1 < N && S[R - L + 1] == S[R + 1]) {
                    
                    ++Z[idx];
                    ++R;
                }
            }
        }
    }
    
    for (int query; M--; ) {
        
        std::cin >> query;
        std::cout << Z[N - query] << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}