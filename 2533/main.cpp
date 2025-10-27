#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N;

std::array<std::vector<int>, 1'000'001> adjL;
std::array<bool, 1'000'001> visited;
std::array<int, 1'000'001> includingRootArray;
std::array<int, 1'000'001> notIncludingRootArray;

void solve(int root) {
    
    int includingRoot = 1, notIncludingRoot = 0;
    
    for (auto& next : adjL[root]) {
        
        if (!visited[next]) {
            
            visited[next] = true;
            solve(next);
            
            includingRoot += std::min(notIncludingRootArray[next], includingRootArray[next]);
            notIncludingRoot += includingRootArray[next];
        }
    }
    
    includingRootArray[root] = includingRoot;
    notIncludingRootArray[root] = notIncludingRoot;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int from, to, res = 0;
    
    for (int idx = 1; idx < N; ++idx) {
        
        std::cin >> from >> to;
        
        adjL[from].push_back(to);
        adjL[to].push_back(from);
    }
    
    std::queue<intPair> q;
    q.push({1, 0});
    visited[1] = true;
    
    solve(1);
    
    std::cout << std::min(notIncludingRootArray[1], includingRootArray[1]);
    
    return 0;
}

