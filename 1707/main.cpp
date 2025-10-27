#include "bits/stdc++.h"


int T, V, E;

std::vector<std::vector<int>> adjL;
std::vector<int> visited;

bool solve(int idx) {
    
    int sw = 1;
    
    std::queue<int> q;
    q.push(idx);
    visited[idx] = 1;
    int front;
    
    while (!q.empty()) {
        
        front = q.front();
        q.pop();
        
        for (auto& el : adjL[front]) {
            
            if (visited[el]) {
                
                if (visited[el] == visited[front]) return false;
            }
            else {
                
                visited[el] = -visited[front];
                q.push(el);
            }
        }
    }
    
    return true;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> V >> E;
        
        adjL.clear();
        visited.clear();
        adjL.resize(V + 1);
        visited.resize(V + 1, 0);
        
        int from, to;
        bool res = true;
        
        while (E--) {
            
            std::cin >> from >> to;
            adjL[from].push_back(to);
            adjL[to].push_back(from);
        }
        
        for (int idx = 1; idx <= V; ++idx) if (!visited[idx]) {
            
            if (!solve(idx)) {
                
                res = false;
                break;
            }
        }
        
        if (res) std::cout << "YES\n";
        else std::cout << "NO\n";
    }
    
    return 0;
}

