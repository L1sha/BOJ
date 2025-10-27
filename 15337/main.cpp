#include "bits/stdc++.h"

constexpr int T_MAX = 200'000;

int T;

std::array<std::pair<int, int>, T_MAX> travels;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> T;
    for (int idx = 0; idx < T; ++idx) {
        
        std::cin >> travels[idx].first >> travels[idx].second;
    }
}

void solve() {
    
    std::sort(travels.begin(), travels.begin() + T);
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>> pq;
    
    std::vector<int> outVec(T);
    int in = 0, out = 0, res1 = 0, res2 = 0;
    
    for (int idx = 0; idx < T; ++idx) {
        
        const auto& [L, R] = travels[idx];
        
        while (!pq.empty() && pq.top().first <= L) {
            
            res1 = std::max(res1, in - outVec[pq.top().second]);
            pq.pop();
            ++out;
        }
        
        outVec[idx] = out;
        
        pq.push({R, idx});
        ++in;
        
        res2 = std::max(res2, in - out);
    }
    
    while (!pq.empty()) {
        
        res1 = std::max(res1, in - outVec[pq.top().second]);
        pq.pop();
    }
    
    std::cout << res1 << ' ' << res2;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}