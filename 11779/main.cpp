#include "bits/stdc++.h"


using intPair = std::pair<int, int>;        
using intTuple = std::tuple<int, int, int>; 

int N, M, start, end;

std::array<std::vector<intPair>, 1001> adjL;
std::array<int, 1001> previousCity;
std::array<bool, 1001> visited;

int Dijkstra() {
    
    std::priority_queue<intTuple, std::vector<intTuple>, std::greater<intTuple>> pq;
    pq.push({0, start, start});
    
    intTuple top;
    int dist, cursor, previous;
    
    while (!pq.empty()) { 
        
        top = pq.top();
        pq.pop();
        
        dist = std::get<0>(top);
        cursor = std::get<1>(top);
        previous = std::get<2>(top);
        
        if (visited[cursor]) continue;
        visited[cursor] = true;
        previousCity[cursor] = previous;
        
        if (cursor == end) break;
        
        for (auto& el : adjL[cursor]) if (!visited[el.second]) pq.push({dist + el.first, el.second, cursor});
    }
    
    return dist;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    int from, to, weight;
    while (M--) {
        
        std::cin >> from >> to >> weight;
        adjL[from].push_back({weight, to});
    }
    
    std::cin >> start >> end;
    
    std::cout << Dijkstra() << '\n';
    
    std::vector<int> route;
    while (end != start) {
        
        route.push_back(end);
        end = previousCity[end];
    }
    route.push_back(end);
    
    std::cout << route.size() << '\n';
    
    std::reverse(route.begin(), route.end());
    for (auto& el : route) std::cout << el << ' ';
    
    return 0;
}


