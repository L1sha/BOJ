#include "bits/stdc++.h"


int N, M, K;

std::array<int, 30001> C;
std::array<std::vector<int>, 30001> adjL;
std::array<bool, 30001> visited;
std::vector<std::pair<int, int>> kidsCycles;  // <#candies, #kids>

void solve(int idx) {
    
    std::queue<int> q;
    q.push(idx);
    int front, cnt = 0, candies = 0;
    
    while (!q.empty()) {
        
        front = q.front();
        q.pop();
        
        if (visited[front]) continue;
        visited[front] = true;
        cnt++;
        candies += C[front];
        
        for (auto& el : adjL[front]) if (!visited[el]) q.push(el);
    }
    
    if (cnt < K) kidsCycles.push_back({candies, cnt});
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> K;
    for (int idx = 1; idx <= N; ++idx) std::cin >> C[idx];
    
    int from, to;
    while (M--) {
        
        std::cin >> from >> to;
        adjL[from].push_back(to);
        adjL[to].push_back(from);
    }

    for (int idx = 1; idx <= N; ++idx) if (!visited[idx]) solve(idx);
    
    std::vector<std::vector<int>> res(K, std::vector<int>(kidsCycles.size() + 1, 0));
    
    for (int kidsNum = 1; kidsNum < K; ++kidsNum) for (int idx = 0; idx < kidsCycles.size(); ++idx) {
        
        if (kidsCycles[idx].second > kidsNum) res[kidsNum][idx + 1] = res[kidsNum][idx];
        else res[kidsNum][idx + 1] = std::max(res[kidsNum - kidsCycles[idx].second][idx] + kidsCycles[idx].first, res[kidsNum][idx]);
    }
    
    std::cout << res.back().back();
    
    return 0;
}

