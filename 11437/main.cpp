#include "bits/stdc++.h"


int N, M, node1, node2;

std::array<std::vector<int>, 50'001> adjL;

std::array<bool, 50'001> visited;
std::array<int, 50'001> height;
std::array<int, 50'001> latest;

void initDFS(int cursor, int depth) {

    visited[cursor] = true;
    height[cursor] = depth;
    
    for (auto& adj : adjL[cursor]) {
        
        if (!visited[adj]) {
            
            latest[adj] = cursor;
            initDFS(adj, depth + 1);
        }
    }
}

int LCA(int node1, int node2) {
    
    if (height[node1] > height[node2]) {
        
        std::swap(node1, node2);
    }
    
    while (height[node1] < height[node2]) {
        
        node2 = latest[node2];
    }
    
    while (node1 != node2) {
        
        node1 = latest[node1];
        node2 = latest[node2];
    }
    
    return node1;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx < N; ++idx) {
        
        std::cin >> node1 >> node2;
        adjL[node1].push_back(node2);
        adjL[node2].push_back(node1);
    }
    
    initDFS(1, 0);
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> node1 >> node2;
        std::cout << LCA(node1, node2) << '\n';
    }
    
    return 0;
}

