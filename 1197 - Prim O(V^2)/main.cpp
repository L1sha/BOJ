#include "bits/stdc++.h"


int V, E;

using intPair = std::pair<int, int>;

std::array<std::vector<intPair>, 10'001> adjL;
std::array<bool, 10'001> visited;
std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> pq;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> V >> E;
    
    int from, to, weight;
    
    while (E--){
        
        std::cin >> from >> to >> weight;
        adjL[from].push_back({weight, to});
        adjL[to].push_back({weight, from});
    }
    
    pq.push({0, 1});
    
    long long res = 0;
    int cnt = 0;
    intPair top;
    
    while (cnt != V){
        
        top = pq.top();
        pq.pop();
        
        if (visited[top.second]) continue;
        visited[top.second] = true;
        cnt++;
        res += top.first;
        
        for (const auto& el : adjL[top.second]) if (!visited[el.second]) pq.push({el.first, el.second});
    }
    
    std::cout << res;
    
    return 0;
}


