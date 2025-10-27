#include "bits/stdc++.h"


int N, R, Q;

std::array<std::vector<int>, 100'001> adjL;
std::array<int, 100'001> nodeNum;
std::array<bool, 100'001> visited;

int solve(int idx) {
    
    visited[idx] = true;
    
    int res = 1;
    for (auto& el : adjL[idx]) if (!visited[el]) res += solve(el);
    
    nodeNum[idx] = res;
    return res;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> R >> Q;
    
    int from, to;
    for (int idx = 0; idx < N - 1; ++idx) {
        
        std::cin >> from >> to;
        adjL[from].push_back(to);
        adjL[to].push_back(from);
    }
    
    solve(R);
    
    while (Q--) {
        
        std::cin >> R;
        std::cout << nodeNum[R] << '\n';
    }
    
    return 0;
}


