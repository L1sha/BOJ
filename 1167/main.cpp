#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N;

std::array<std::vector<intPair>, 100'001> adjL;
std::array<int, 100'001> max;
std::array<bool, 100'001> visited;

intPair DFS(int idx) {      // first: ans, second: maxHeight
    
    visited[idx] = true;
    
    intPair temp;
    int max = 0, first = 0, second = 0;
    
    for (auto& el : adjL[idx]) if (!visited[el.second]) {
        
        temp = DFS(el.second);
        
        if (first < el.first + temp.second) {
            
            second = first;
            first = el.first + temp.second;
        }
        else if (second < el.first + temp.second) second = el.first + temp.second;
        max = std::max(max, temp.first);
    }
    
    return {std::max(first + second, max), first};
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int from, to, weight;
    
    for (int idx = 1; idx <= N; ++idx){
        
        std::cin >> from;
        std::cin >> to;
        
        while (to != -1){
            
            std::cin >> weight;
            adjL[from].push_back({weight, to});
            adjL[to].push_back({weight, from});
            std::cin >> to;
        }
    }
    
    std::cout << DFS(1).first;
    
    return 0;
}



