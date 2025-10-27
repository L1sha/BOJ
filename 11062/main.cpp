#include "bits/stdc++.h"

constexpr int N_MAX = 10'000;

int T, N;

std::vector<int> cards;
std::vector<std::vector<std::pair<int, int>>> dp;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    cards.clear();
    cards.resize(N);
    dp.clear();
    dp.resize(N, std::vector<std::pair<int, int>>(N));
    
    for (auto& el : cards) std::cin >> el;
}

void solve() {
    
    for (int idx = 0; idx < N; ++idx) dp[idx][idx] = {cards[idx], 0};
    
    for (int idx = 0; idx < N - 1; ++idx) {
        
        if (cards[idx] > cards[idx + 1]) {
            
            dp[idx][idx + 1] = {cards[idx], 0};
        }
        else {
            
            dp[idx][idx + 1] = {cards[idx + 1], 1};
        }
    }
    
    for (int dist = 2; dist < N; ++dist) {
        
        for (int idx = 0; idx < N - dist; ++idx) {
            
            int left = cards[idx], right = cards[idx + dist];
            
            if (dp[idx + 1][idx + dist].second == 0) {
                
                left += dp[idx + 2][idx + dist].first;
            }
            else {
                
                left += dp[idx + 1][idx + dist - 1].first;
            }
            
            if (dp[idx][idx + dist - 1].second == 0) {
                
                right += dp[idx + 1][idx + dist - 1].first;
            }
            else {
                
                right += dp[idx][idx + dist - 2].first;
            }
            
            if (left > right) dp[idx][idx + dist] = {left, 0};
            else dp[idx][idx + dist] = {right, 1};
        }
    }
    
    std::cout << dp[0][N - 1].first << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    int T; std::cin >> T;
    while (T--) {
        
        get_input();
        solve();
    }
    
    return 0;
}