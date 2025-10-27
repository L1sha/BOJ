#include "bits/stdc++.h"

using intPair = std::pair<int, int>;

int N, M, X;

std::array<std::vector<intPair>, 1001> adjL;
std::array<std::vector<intPair>, 1001> reverseAdjL;

std::array<bool, 1001> visited;
std::array<bool, 1001> reverseVisited;
std::array<int, 1001> res;
std::array<int, 1001> reverseRes;



void solve(const std::array<std::vector<intPair>, 1001>& adjL, std::array<int, 1001>& res, std::array<bool, 1001>& visited, int idx){
    
    std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> pq;
    pq.push({0, idx});
    
    intPair temp;
    
    while (!pq.empty()){
        
        temp = pq.top();
        pq.pop();
        
        if (visited[temp.second]) continue;
        visited[temp.second] = true;
        res[temp.second] = temp.first;
        
        for (auto& el : adjL[temp.second]) if (!visited[el.second]) pq.push({temp.first + el.first, el.second});
    }
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> X;
    
    int from, to, weight;
    
    while (M--){
        
        std::cin >> from >> to >> weight;
        adjL[from].push_back({weight, to});
        reverseAdjL[to].push_back({weight, from});
    }
    
    solve(adjL, res, visited, X);
    solve(reverseAdjL, reverseRes, reverseVisited, X);
    
    for (int idx = 1; idx <= N; ++idx) res[idx] += reverseRes[idx];
    
    std::cout << *std::max_element(res.begin() + 1, res.begin() + N + 1);
    
    return 0;
}


