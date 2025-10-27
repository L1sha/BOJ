#include "bits/stdc++.h"


// Kosaraju's algorithm

int N, E;

std::array<std::vector<int>, 10'001> adjL, backAdjL;
std::array<int, 10'001> finishedOrder;
std::bitset<10'001> visited;

void subDFS(int cursor, int& cnt) {
    
    visited[cursor] = true;
    
    for (const int& next : adjL[cursor]) {
        
        if (!visited[next]) {
            
            subDFS(next, cnt);
        }
    }
    
    finishedOrder[++cnt] = cursor;
}

void DFS() {
    
    int cnt = 0;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (!visited[idx]) {
            
            subDFS(idx, cnt);
        }
    }
}

void subBackDFS(int cursor, std::vector<int>& res) {
    
    visited[cursor] = true;
    res.push_back(cursor);
    
    for (const int& next : backAdjL[cursor]) {
        
        if (!visited[next]) {
            
            subBackDFS(next, res);
        }
    }
}

bool compareIntVector(const std::vector<int>& A, const std::vector<int>& B) {
    
    return A.front() < B.front();
}

std::vector<std::vector<int>> backDFS() {
    
    std::vector<std::vector<int>> SCC;
    
    for (int idx = N; idx >= 1; --idx) {
        
        if (!visited[finishedOrder[idx]]) {
            
            std::vector<int> newSCC;
            
            subBackDFS(finishedOrder[idx], newSCC);
            
            std::sort(newSCC.begin(), newSCC.end());
            SCC.push_back(std::move(newSCC));
        }
    }
    
    std::sort(SCC.begin(), SCC.end(), compareIntVector);
    
    return SCC;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> E;

    int from, to;
    
    while (E--) {
        
        std::cin >> from >> to;
        adjL[from].push_back(to);
        backAdjL[to].push_back(from);
    }
    
    DFS();
    
    visited.reset();
    
    auto res = backDFS();
    
    std::cout << res.size() << '\n';
    
    for (const auto& SCC : res) {
        
        for (const auto& el : SCC) {
            
            std::cout << el << ' ';
        }
        
        std::cout << -1 << '\n';
    }
    
    return 0;
}

