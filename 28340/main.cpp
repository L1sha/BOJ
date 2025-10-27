#include "bits/stdc++.h"

constexpr int N_MAX = 10'000, K_MAX = 10'000;

int N, K;
std::vector<int> freq, depth;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K;
    
    freq.resize(N);
    for (auto& el : freq) std::cin >> el;
    
    depth.resize(N);
    std::fill(depth.begin(), depth.end(), 1);
}

void solve() {
    
    std::priority_queue<long long, std::vector<long long>, std::greater<>> pq;
    long long res = 0, sum;
    
    for (const auto& el : freq) {
        
        pq.push(el);
        res += el;
    }
    
    if (N > K && (N - K) % (K - 1) != 0) {
        
        sum = 0;
        
        for (int idx = 0; idx <= (N - K) % (K - 1); ++idx) {
            
            sum += pq.top();
            res += pq.top();
            pq.pop();
        }
        
        pq.push(sum);
    }
    
    while (pq.size() > K) {
        
        sum = 0;
        
        for (int idx = 0; idx < K; ++idx) {
            
            sum += pq.top();
            res += pq.top();
            pq.pop();
        }
        
        pq.push(sum);
    }
    
    std::cout << res << '\n';
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