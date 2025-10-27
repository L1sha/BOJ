#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;

int N;
std::array<char, N_MAX * 2 + 2> S;
std::array<int, N_MAX * 2 + 2> manacher;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    N = 1;
    S[0] = '.';
    
    while (std::cin >> S[N]) {
        
        S[++N] = '.';
        ++N;
    }
}

void solve() {
    
    int P = -1, R = -1;
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (idx > R) {
            
            manacher[idx] = 1;
            P = idx;
            R = idx;
            
            while (R + 1 < N && P - (R + 1 - P) >= 0
                && S[R + 1] == S[P - (R + 1 - P)]) {
                
                ++R;
                manacher[idx] += 2;
            }
        }
        else {
            
            if (manacher[P - (idx - P)] < 2 * (R - idx) + 1) {
                
                manacher[idx] = manacher[P - (idx - P)];
            }
            else if (manacher[P - (idx - P)] > 2 * (R - idx) + 1) {
                
                manacher[idx] = 2 * (R - idx) + 1;
            }
            else {
                
                manacher[idx] = 2 * (R - idx) + 1;
                P = idx;
                
                while (R + 1 < N && P - (R + 1 - P) >= 0
                    && S[R + 1] == S[P - (R + 1 - P)]) {
                    
                    ++R;
                    manacher[idx] += 2;
                }
            }
        }
    }
    
    std::cout << (*std::max_element(manacher.begin(), manacher.begin() + N) - 1) / 2;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}