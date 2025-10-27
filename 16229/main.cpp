#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;

int N, K;
std::string S;

std::array<int, N_MAX> Z;

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K >> S;
}

void makeZ() {
    
    Z[0] = N;
    int L = 0, R = 0;
    
    for (int idx = 1; idx < N; ++idx) {
        
        if (idx > R) {
            
            if (S[idx] == S[0]) {
                
                L = idx;
                R = idx;
                ++Z[idx];
                
                while (R + 1 < N && S[R - L + 1] == S[R + 1]) {
                    
                    ++R;
                    ++Z[idx];
                }
            }            
        }
        else {  // L <= idx <= R
            
            if (Z[idx - L] < R - idx + 1) {
                
                Z[idx] = Z[idx - L];
            }
            else {
                
                L = idx;
                Z[idx] = R - idx + 1;
                
                while (R + 1 < N && S[R - L + 1] == S[R + 1]) {
                    
                    ++R;
                    ++Z[idx];
                }
            }
        }
    }
}

void solve() {
    
    if (K >= N) {
        
        std::cout << N;
        return;
    }
    
    makeZ();
    
    for (int pattern = (N + K) / 2; pattern > 0; --pattern) {
        
        if (N % pattern != 0 && (N / pattern + 1) * pattern > N + K) continue;
        
        bool flag = true;
        int cursor = pattern;
        
        for (; cursor + pattern < N; cursor += pattern) {
            
            if (Z[cursor] < pattern) {
                
                flag = false;
                break;
            }
        }
        
        if (flag && Z[cursor] == N - cursor) {
            
            std::cout << pattern;
            return;
        }
    }
    
    std::cout << 0;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}