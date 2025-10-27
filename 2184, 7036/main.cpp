#include "bits/stdc++.h"

constexpr int N_MAX = 1001;
constexpr long long LL_MAX = 1e18;

int N, L;

std::array<int, N_MAX> xCoord;
std::array<std::array<std::array<std::optional<long long>, 2>, N_MAX>, N_MAX> dp;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> L;
    for (int idx = 0; idx < N; ++idx) std::cin >> xCoord[idx];
    
    xCoord[N] = L;
    std::sort(xCoord.begin(), xCoord.begin() + N + 1);
    
    for (int idx = 0; idx <= N; ++idx) {
        
        if (xCoord[idx] == L) {
            
            L = idx;
            break;
        }
    }
}

long long getAns(int l, int r, int isRight) {
    
    if (r < L || l > L) return LL_MAX;
    if (l == r) return 0;
    if (dp[l][r][isRight].has_value()) return dp[l][r][isRight].value();
    
    if (isRight) {
        
        if (r == L) return LL_MAX;
        
        return (dp[l][r][isRight] = std::min(
            getAns(l, r - 1, 1) + (N + 1 - (r - l)) * (xCoord[r] - xCoord[r - 1]),
            getAns(l, r - 1, 0) + (N + 1 - (r - l)) * (xCoord[r] - xCoord[l])
            )).value();
    }
    else {
        
        if (l == L) return LL_MAX;
        
        return (dp[l][r][isRight] = std::min(
            getAns(l + 1, r, 1) + (N + 1 - (r - l)) * (xCoord[r] - xCoord[l]),
            getAns(l + 1, r, 0) + (N + 1 - (r - l)) * (xCoord[l + 1] - xCoord[l])
            )).value();
    }
}

void solve() {
    
    std::cout << std::min(getAns(0, N, 0), getAns(0, N, 1));
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}