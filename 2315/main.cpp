#include "bits/stdc++.h"

constexpr int N_MAX = 1'001;
constexpr long long ANS_MAX = 1'000'000'001;

int N, M;

std::array<long long, N_MAX> D, W, S;

std::array<std::array<std::array<std::optional<long long>, 2>, N_MAX>, N_MAX> dp;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> D[idx] >> W[idx];
        S[idx] += S[idx - 1] + W[idx];
    }
}

long long getAns(int l, int r, int isRight) {
    
    if (M < l || M > r) return ANS_MAX;
    if (l == r) return 0;
    if (dp[l][r][isRight].has_value()) return dp[l][r][isRight].value();
    
    if (isRight) {
        
        if (r == M) return ANS_MAX;
        
        long long cand1 = getAns(l, r - 1, 0)
            + (D[r] - D[l]) * (S[N] - S[r - 1] + S[l - 1]);
        
        long long cand2 = getAns(l, r - 1, 1)
            + (D[r] - D[r - 1]) * (S[N] - S[r - 1] + S[l - 1]);
        
        return (dp[l][r][isRight] = std::min(cand1, cand2)).value();
    }
    else {
        
        if (l == M) return ANS_MAX;
        
        long long cand1 = getAns(l + 1, r, 0)
            + (D[l + 1] - D[l]) * (S[N] - S[r] + S[l]);
        
        long long cand2 = getAns(l + 1, r, 1)
            + (D[r] - D[l]) * (S[N] - S[r] + S[l]);
        
        return (dp[l][r][isRight] = std::min(cand1, cand2)).value();
    }
}

void solve() {
    
    std::cout << std::min(getAns(1, N, 0), getAns(1, N, 1));
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}