#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, E, v1, v2;

std::array<std::vector<intPair>, 801> adjL;


int Dijkstra(int start, int end) {
    
    std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> pq;
    pq.push({0, start});
    
    std::vector<bool> visited(N + 1, false);
    intPair top;
    
    while (!pq.empty()) {
        
        top = pq.top();
        pq.pop();
        
        if (visited[top.second]) continue;
        visited[top.second] = true;
        
        if (top.second == end) return top.first;
        
        for (auto& el : adjL[top.second]) if (!visited[el.second]) pq.push({el.first + top.first, el.second});
    }
    
    return -1;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> E;
    
    int from, to, weight;
    
    while (E--) {
        
        std::cin >> from >> to >> weight;
        adjL[from].push_back({weight, to});
        adjL[to].push_back({weight, from});
    }
    
    std::cin >> v1 >> v2;
    
    int res1 = 0, res2 = 0, temp;
    bool possible1 = true, possible2 = true;
    

        
    temp = Dijkstra(1, v1);
    if (temp == -1) possible1 = false;
    res1 += temp;
    
    temp = Dijkstra(v1, v2);
    if (temp == -1) possible1 = false;
    res1 += temp;
    
    temp = Dijkstra(v2, N);
    if (temp == -1) possible1 = false;
    res1 += temp;
    
    
    temp = Dijkstra(1, v2);
    if (temp == -1) possible2 = false;
    res2 += temp;
    
    temp = Dijkstra(v2, v1);
    if (temp == -1) possible2 = false;
    res2 += temp;
    
    temp = Dijkstra(v1, N);
    if (temp == -1) possible2 = false;
    res2 += temp;
    
    if (possible1) {
        
        if (possible2) std::cout << std::min(res1, res2);
        else std::cout << res1;
    }
    else {
        
        if (possible2) std::cout << res2;
        else std::cout << -1;
    }
    
    return 0;
}


