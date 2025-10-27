#include "bits/stdc++.h"


int N, M, node1, node2;
constexpr int MAX = std::ceil(log2(100'001));

std::array<std::vector<int>, 100'001> adjL;

std::array<int, 100'001> height;
std::array<std::array<int, MAX>, 100'001> parents;

void initDFS(int cursor, int parent) {

    height[cursor] = height[parent] + 1;
    
    parents[cursor][0] = parent;
    for (int idx = 1; idx < MAX; ++idx) {
        
        parents[cursor][idx] = parents[parents[cursor][idx - 1]][idx - 1];
        
        if (parents[cursor][idx] == 0) {
            
            break;
        }
    }
    
    for (auto& adj : adjL[cursor]) {
        
        if (adj != parent) {
          
            initDFS(adj, cursor);
        }
    }
}

int LCA(int node1, int node2) {
    
    if (height[node1] > height[node2]) {
        
        std::swap(node1, node2);
    }
    
    if (node1 == 1) {
        
        return 1;
    }
    
    // Now, height[node1] & height[node2] >= 1
    
    for (int idx = MAX - 1; idx >= 0; --idx) {
        
        if (height[parents[node2][idx]] >= height[node1]) {
            
            node2 = parents[node2][idx];
        }
    }
    
    if (node1 == node2) {
        
        return node1;
    }
    
    // Now, node1 and node2 are on same height & node1 != node2
    
    // pull up node1 and node2 right before their LCA
    
    for (int idx = MAX - 1; idx >= 0; --idx) {
        
        if (parents[node1][idx] != parents[node2][idx]) {
            
            node1 = parents[node1][idx];
            node2 = parents[node2][idx];
        }            
    }
    
    return parents[node1][0];
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
    
    height[0] = -1;
    initDFS(1, 0);
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> node1 >> node2;
        std::cout << LCA(node1, node2) << '\n';
    }
    
    return 0;
}

