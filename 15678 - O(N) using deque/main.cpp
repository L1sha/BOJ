#include "bits/stdc++.h"


int N, D;
std::array<long long, 100'001> K;

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> D;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> K[idx];
    }
    
    std::deque<std::pair<long long, int>> dq;
    
    dq.push_back({K[0], 0});
    long long res = K[0], temp;
    
    for (int idx = 1; idx < N; ++idx) {
        
        while (idx - dq.front().second > D) {
            
            dq.pop_front();
        }
        
        temp = std::max(K[idx], dq.front().first + K[idx]);
        
        while (!dq.empty() && temp > dq.back().first) {
            
            dq.pop_back();
        }
        
        dq.push_back({temp, idx});
        res = std::max(res, temp);
    }
    
    std::cout << res;
    
    return 0;
}

