#include "bits/stdc++.h"


int V, E, K;

using intPair = std::pair<int, int>;

std::array<std::vector<intPair>, 20'001> adjL;
// intPair : <distance, destination>
std::array<int, 20'001> minDist;
std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> pq;
// intPair : <distance sum, current position>

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> V >> E >> K;
    
    int u, v, w;
    
    while (E--){
        
        std::cin >> u >> v >> w;
        adjL[u].push_back({w, v});
    }
    
    std::fill(minDist.begin(), minDist.begin() + V + 1, -1);
    
    pq.push({0, K});
    
    intPair top;
    
    while (!pq.empty()){
        
        top = pq.top();
        pq.pop();
        
        if (minDist[top.second] != -1) continue;
        minDist[top.second] = top.first;
        
        for (const intPair& el : adjL[top.second]) if (minDist[el.second] == -1) pq.push({top.first + el.first, el.second});
    }
    
    for (int idx = 1; idx <= V; ++idx){
        
        if (minDist[idx] == -1) std::cout << "INF\n";
        else std::cout << minDist[idx] << '\n';
    }
    
    return 0;
}


