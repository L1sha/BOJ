#include "bits/stdc++.h"


constexpr int N_MAX = 10'001, K_MAX = 20;

using intPair = std::pair<int, int>;
using route = std::pair<std::pair<long long, int>, int>;

int N, M, K;

std::array<std::vector<intPair>, N_MAX> adjL;
std::array<std::array<long long, K_MAX>, N_MAX> res;

void get_input() {
    
    std::cin >> N >> M >> K;
    for (int from, to, dist; M--;) {
        
        std::cin >> from >> to >> dist;
        adjL[from].push_back({dist, to});
        adjL[to].push_back({dist, from});
    }
}

void solve() {
    //dijkstra
    
    for (int idx = 1; idx <= N; ++idx) std::fill(res[idx].begin(), res[idx].begin() + K + 1, LLONG_MAX);
    
    std::priority_queue<route, std::vector<route>, std::greater<route>> pq;
    pq.push({{0, 0}, 1});
    res[1][0] = 0;
    
    long long distSum;
    int cnt, cursor;
    
    while (!pq.empty()) {
        
        distSum = pq.top().first.first;
        cnt = pq.top().first.second;
        cursor = pq.top().second;
        pq.pop();
        
        if (cursor == N) {
            
            std::cout << distSum;
            return;
        }
        
        if (distSum > res[cursor][cnt]) continue;
        
        for (const auto& [dist, next] : adjL[cursor]) {
            
            if (distSum + dist < res[next][cnt]) {
                
                res[next][cnt] = distSum + dist;
                pq.push({{distSum + dist, cnt}, next});
            }
            
            if (cnt < K && distSum < res[next][cnt + 1]) {
                
                res[next][cnt + 1] = distSum;
                pq.push({{distSum, cnt + 1}, next});
            }
        }
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

