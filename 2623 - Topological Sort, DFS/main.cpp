#include "bits/stdc++.h"


int N, M, S;

std::array<std::vector<int>, 1001> adjL;
std::array<bool, 1001> visited;
std::array<bool, 1001> visitedDFS;
std::array<std::unordered_set<int>, 1001> onlyOne;
std::vector<int> res;
std::stack<int> s;


bool DFS(int idx){
    
    if (visited[idx]) return false;
    
    if (visitedDFS[idx]) return true;       // cycle detected
    visitedDFS[idx] = true;
    
    for (auto& el : adjL[idx]) if (DFS(el)) return true;
    
    res.push_back(idx);
    visited[idx] = true;
    
    return false;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    int from, to;
    
    while (M--){
        
        std::cin >> S;
        
        std::cin >> from;

        while (--S){
            
            std::cin >> to;
            
            if (onlyOne[from].find(to) == onlyOne[from].end()){
                
                adjL[from].push_back(to);
                onlyOne[from].insert(to);    
            }
            
            from = to;
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) if (DFS(idx)) { std::cout << 0; return 0; }
    
    std::reverse(res.begin(), res.end());
    for (auto& el : res) std::cout << el << '\n';
    
    return 0;
}





