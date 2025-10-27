#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M, start, end;

std::array<std::vector<intPair>, 1001> adjL;
std::array<bool, 1001> visited;
std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> pq;


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
    
    pq.push({0, start});
    intPair temp;
    
    while (!pq.empty()) {
        
        temp = pq.top();
        pq.pop();
        
        if (visited[temp.second]) continue;
        visited[temp.second] = true;
        
        if (temp.second == end) break;
        
        for (auto& el : adjL[temp.second]) if (!visited[el.second]) pq.push({temp.first + el.first, el.second});
    }
    
    std::cout << temp.first;
    
    return 0;
}


