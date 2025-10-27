#include "bits/stdc++.h"


constexpr int N_MAX = 1'001, K_MAX = 30'000;

using intPair = std::pair<int, int>;
using route = std::pair<intPair, int>;

int N, M, K, S, D;
std::array<std::vector<intPair>, N_MAX> adjL;
std::array<std::vector<intPair>, N_MAX> res;
std::array<int, K_MAX> tax;


void get_input() {
    
    std::cin >> N >> M >> K >> S >> D;
    
    for (int from, to, fee; M; --M) {
        
        std::cin >> from >> to >> fee;
        adjL[from].push_back({fee, to});
        adjL[to].push_back({fee, from});
    }
    
    for (int idx = 0; idx < K; ++idx) std::cin >> tax[idx];
}

void dijkstra() {
    
    std::priority_queue<route, std::vector<route>, std::greater<route>> pq;
    pq.push({{0, 0}, S});
    
    for (int totalFee, numRoad, cursor, sz; !pq.empty();) {
        
        totalFee = pq.top().first.first;
        numRoad = pq.top().first.second;
        cursor = pq.top().second;
        pq.pop();
        
        if (!res[cursor].empty() && numRoad >= res[cursor].back().second) continue;
        
        while ((sz = res[cursor].size()) >= 2 && 
        (res[cursor][sz - 1].first - res[cursor][sz - 2].first) * (res[cursor][sz - 1].second - numRoad)
        >= (totalFee - res[cursor][sz - 1].first) * (res[cursor][sz - 2].second - res[cursor][sz - 1].second)) {
            
            res[cursor].pop_back();
        }
        res[cursor].push_back({totalFee, numRoad});
        
        for (const auto& [fee, next] : adjL[cursor]) {
            
            if (!res[next].empty() && numRoad + 1 >= res[next].back().second) continue;
            pq.push({{totalFee + fee, numRoad + 1}, next});
        }
    }
}

void solve() {
    
    dijkstra();
    
    std::cout << res[D].front().first << '\n';
    
    for (long long idx = 0, taxSum = 0, cursor = 0, sz = res[D].size(); idx < K; ++idx) {
        
        taxSum += tax[idx];
        while (cursor < sz - 1 &&
        res[D][cursor].first + res[D][cursor].second * taxSum
        >= res[D][cursor + 1].first + res[D][cursor + 1].second * taxSum) {
            
            cursor++;
        }
        
        std::cout << res[D][cursor].first + res[D][cursor].second * taxSum << '\n';
    }
} 


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    get_input();
    
    solve();
    
    return 0;
}

