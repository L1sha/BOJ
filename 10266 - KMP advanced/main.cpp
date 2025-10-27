#include "bits/stdc++.h"


constexpr int N_MAX = 200'000;

int N;

std::array<int, N_MAX> clock1, clock2, KMP;

void init() {
    
    for (int idx = N - 1; idx >= 0; --idx) clock1[idx] -= clock1[0];
    
    int corrected = 0, base = clock1[1];
    
    for (int idx = 2; idx < N - 1; ++idx) {
        
        if (clock1[corrected + 1] == clock1[idx] - base) {
            
            KMP[idx] = ++corrected;
        }
        else if (corrected) {
            
            corrected = KMP[idx];
            
            base = clock1[idx - 1 - corrected];
            
            idx--;
        }
        else {
            
            base = clock1[idx];
        }
    }
}

int solve() {
    
    std::sort(clock1.begin(), clock1.begin() + N);
    std::sort(clock2.begin(), clock2.begin() + N);
    
    init();
    
    int corrected = 0, base = clock2[0] - 360'000;
    
    for (int idx = 1; idx < 2 * N - 1; ++idx) {
        
        if (clock1[corrected + 1] == (clock2[idx % N] - base) % 360'000) {
            
            corrected++;
            
            if (corrected == N - 1) {
                
                return true;
            }
        }
        else if (corrected) {
            
            corrected = KMP[corrected];
            
            if (idx - 1 - corrected >= N) return false;
            base = clock2[idx - 1 - corrected] - 360'000;
            
            idx--;
        }
        else {
            
            if (idx >= N) return false;
            base = clock2[idx] - 360'000;
        }
    }
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> clock1[idx];
    for (int idx = 0; idx < N; ++idx) std::cin >> clock2[idx];
    
    if (solve()) std::cout << "possible";
    else std::cout << "impossible";
    
    return 0;
}

