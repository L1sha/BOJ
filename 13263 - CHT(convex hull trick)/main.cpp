#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;

int N;

std::array<long long, N_MAX> A, B;
std::array<long long, N_MAX> memo;
std::array<long double, N_MAX> starting;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> A[idx];
    for (int idx = 0; idx < N; ++idx) std::cin >> B[idx];
}

void solve() {
    
    std::vector<int> idxSurvived;
    idxSurvived.push_back(0);
    starting[0] = 0;
    
    for (int l, r, mid, back, idx = 1; idx < N; ++idx) {
        
        l = 0;
        r = idxSurvived.size();
        
        while (r - l > 1) {
            
            mid = (l + r) / 2;
            
            if (starting[idxSurvived[mid]] <= A[idx]) l = mid;
            else r = mid;
        }
        
        memo[idx] = A[idx] * B[idxSurvived[l]] + memo[idxSurvived[l]];
        
        while (true) {
            
            back = idxSurvived.back();
            
            starting[idx] = ((long double) memo[idx] - memo[back]) / (B[back] - B[idx]);
            
            if (starting[back] >= starting[idx]) {
                
                idxSurvived.pop_back();
            }
            else {
                
                idxSurvived.push_back(idx);
                break;
            }
        }
    }
    
    std::cout << memo[N - 1];
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}