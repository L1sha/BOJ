#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, A, B, C, cnt;
std::array<int, 100'001> energy, res;
std::array<std::vector<intPair>, 100'001> adjL;
std::array<std::pair<int, int>, 100'000> stack;
std::bitset<100'001> visited;

void DFS(int cursor, int depth) {
    
    visited[cursor] = true;
    stack[cnt++] = {depth, cursor};
    res[cursor] = (*std::lower_bound(stack.begin(), stack.begin() + cnt, std::make_pair(depth - energy[cursor], 0))).second;
    
    for (const auto& [dist, next] : adjL[cursor]) {
        
        if (!visited[next]) {
            
            DFS(next, depth + dist);
        }
    }
    
    cnt--;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> energy[idx];
    }
    for (int idx = 1; idx < N; ++idx) {
        
        std::cin >> A >> B >> C;
        adjL[A].push_back({C, B});
        adjL[B].push_back({C, A});
    }
    
    DFS(1, 0);
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cout << res[idx] << '\n';
    }
    
    return 0;
}

