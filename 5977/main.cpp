#include "bits/stdc++.h"


constexpr int N_MAX = 100'000;

int N, K;

std::array<long long, N_MAX> eff;

long long solve() {
    
    std::deque<std::pair<long long, int>> dq;
    /*
    <first: current score, second: latest blank>
    In deque, first: always descending order & second: always ascending order
    */
    long long sum = eff[0], res = -1;
    
    if (eff[0] != 0) {
        
        dq.push_back({0, -1});
    }
    dq.push_back({-eff[0], 0});
    
    for (int idx = 1; idx < N; ++idx) {
        
        while (!dq.empty() && dq.back().first <= dq.front().first - eff[idx]) {
            
            dq.pop_back();
        }
        
        dq.push_back({dq.front().first - eff[idx], idx});
        
        if (idx - dq.front().second > K) {
            
            res = std::max(res, dq.front().first + sum);
            dq.pop_front();
        }
        
        sum += eff[idx];
    }
    
    return std::max(res, dq.front().first + sum);
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> eff[idx];
    }
    
    std::cout << solve();
    
    return 0;
}

