#include "bits/stdc++.h"


constexpr int N_MAX = 1001, M_MAX = 1001;

int N, M, workNum, work;

std::array<std::vector<int>, N_MAX> ableWorks;
std::array<int, M_MAX> occupied;
std::bitset<M_MAX> visited;

int solve(int idx) {
    
    for (const auto& work : ableWorks[idx]) {
        
        if (visited[work]) continue;
        visited[work] = true;
        
        if (occupied[work] == 0 || solve(occupied[work])) {
            
            occupied[work] = idx;
            return 1;
        }
    }
    
    return 0;
}

int solve() {
    
    int res = 0;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        visited.reset();
        res += solve(idx);
    }
    
    return res;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> workNum;
        ableWorks[idx].resize(workNum);
        
        for (auto& el : ableWorks[idx]) std::cin >> el;
        std::sort(ableWorks[idx].begin(), ableWorks[idx].end());
    }
    
    std::cout << solve();
    
    return 0;
}

