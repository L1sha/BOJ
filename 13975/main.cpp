#include "bits/stdc++.h"

constexpr int N_MAX = 1'000'000;

int N;
std::vector<int> files;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    files.resize(N);
    for (auto& el : files) std::cin >> el;
}

void solve() {
    
    std::priority_queue<long long, std::vector<long long>, std::greater<>> pq;
    
    for (const auto& el : files) pq.push(el);
    
    long long res = 0, sum;
    
    while (pq.size() > 1) {
        
        sum = pq.top();
        pq.pop();
        sum += pq.top();
        pq.pop();
        
        res += sum;
        
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