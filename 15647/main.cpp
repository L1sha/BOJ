#include "bits/stdc++.h"

constexpr int N_MAX = 300'001;

long long N;

std::array<std::vector<std::pair<int, long long>>, N_MAX> adjL;
std::array<long long, N_MAX> subTreeSum, subTreeCnt, res;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int node1, node2, dist, idx = 0; idx < N - 1; ++idx) {
        
        std::cin >> node1 >> node2 >> dist;
        
        adjL[node1].push_back({node2, dist});
        adjL[node2].push_back({node1, dist});
    }
}

void DFS1(int curr = 1, int prev = 0) {
    
    subTreeCnt[curr] = 1;
    
    for (const auto& [next, dist] : adjL[curr]) {
        
        if (next != prev) {
            
            DFS1(next, curr);
            
            subTreeCnt[curr] += subTreeCnt[next];
            subTreeSum[curr] += subTreeSum[next];
            subTreeSum[curr] += dist * subTreeCnt[next];
        }
    }
}

void DFS2(int curr = 1, int prev = 0, long long sum = 0) {
    
    sum += subTreeSum[curr];
    
    res[curr] = sum;
    
    for (const auto& [next, dist] : adjL[curr]) {
        
        if (next != prev) {
            
            DFS2(next, curr,
                sum - subTreeSum[next] + dist * (N - 2 * subTreeCnt[next]));
        }
    }
} 

void solve() {
    
    DFS1();
    DFS2();
    
    for (int idx = 1; idx <= N; ++idx) std::cout << res[idx] << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}