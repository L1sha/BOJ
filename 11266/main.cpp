#include "bits/stdc++.h"


int V, E, cnt;
std::array<std::vector<int>, 10'001> adjL;
std::bitset<10'001> res;
std::array<int, 10'001> visited;


int articulationPoint(int cursor, bool isParent) {
    
    visited[cursor] = ++cnt;
    int lowest = cnt, child_cnt = 0;
    
    for (const int& next : adjL[cursor]) {
        
        if (visited[next]) {
            
            lowest = std::min(lowest, visited[next]);
        }
        else {
            
            int temp = articulationPoint(next, false);
            lowest = std::min(lowest, temp);
            
            if (isParent) {
                
                child_cnt++;
            }
            else if (temp == visited[cursor]) {
                
                res[cursor] = true;
            }
        }
    }
    
    if (isParent) {
        
        if (child_cnt >= 2) {
            
            res[cursor] = true;
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
            
            articulationPoint(idx, true);
        }
    }
    
    std::cout << res.count() << '\n';
    
    for (int idx = 1; idx <= V; ++idx) {
        
        if (res[idx]) {
            
            std::cout << idx << ' ';
        }
    }
    
    return 0;
}

