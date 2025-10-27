#include "bits/stdc++.h"

constexpr int N_MAX = 50, T_MAX = 100'001;

long long N, T;

struct Problem {
    
    long long M, P, R;
    
    bool operator< (const Problem& rhs) {
        
        return R * rhs.P < rhs.R * P;
    }
};

std::array<Problem, N_MAX> problems;
std::array<long long, T_MAX> res, toUpdate;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> T;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> problems[idx].M;
    for (int idx = 0; idx < N; ++idx) std::cin >> problems[idx].P;
    for (int idx = 0; idx < N; ++idx) std::cin >> problems[idx].R;
}

void solve() {
    
    std::sort(problems.begin(), problems.begin() + N);
    
    for (int idx = 0; idx < N; ++idx) {
        
        auto [M, P, R] = problems[idx];
        
        for (long long t = 0; t < T; ++t) {
            
            if (t + R <= T) {
                
                toUpdate[t + R] = std::max(toUpdate[t + R],
                    res[t] + M - (t + R) * P);
            }
        }
        
        for (int t = 0; t <= T; ++t) res[t] = toUpdate[t];
    }
    
    std::cout << *std::max_element(res.begin(), res.begin() + T + 1);
}


int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}