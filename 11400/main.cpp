#include "bits/stdc++.h"


int V, E, cnt;
std::array<std::vector<int>, 100'001> adjL;
std::vector<std::pair<int, int>> res;
std::array<int, 100'001> visited;

int articulationBridge(const int& cursor, int parent) {
    
    int lowest = visited[cursor] = ++cnt;
    
    for (const int& next : adjL[cursor]) {
        
        if (visited[next]) {
            
            if (next != parent) {
                
                lowest = std::min(lowest, visited[next]);
            }
        }
        else {
            
            int temp = articulationBridge(next, cursor);
            lowest = std::min(lowest, temp);
            
            if (temp == visited[next]) {
                
                res.push_back({std::min(cursor, next), std::max(cursor, next)});
            }
        }
    }
    
    return lowest;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> V >> E;
    
    int from, to;
    while (E--) {
        
        std::cin >> from >> to;
        adjL[from].push_back(to);
        adjL[to].push_back(from);
    }
    
    for (int idx = 1; idx <= V; ++idx) {
        
        if (!visited[idx]) {
            
            articulationBridge(idx, 0);
        }
    }
    
    std::sort(res.begin(), res.end());
    
    std::cout << res.size() << '\n';
    
    for (const auto& el : res) {
        
        std::cout << el.first << ' ' << el.second << '\n';
    }
    
    return 0;
}

