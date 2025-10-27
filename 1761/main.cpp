#include "bits/stdc++.h"


int N, M, n1, n2, d;
constexpr int MAX = std::ceil(log2(40'000));

std::array<std::vector<std::pair<int, int>>, 40'001> adjL;

std::array<int, 40'001> height;
std::array<std::array<std::pair<long long, int>, MAX>, 40'001> parents;

void initDFS(int cursor, int parent, int dist) {
    
    height[cursor] = height[parent] + 1;
    
    parents[cursor][0] = {dist, parent};
    
    for (int idx = 1; idx < MAX; ++idx) {
        
        parents[cursor][idx].second = parents[parents[cursor][idx - 1].second][idx - 1].second;
        
        if (parents[cursor][idx].second == 0) {
            
            break;
        }
        
        parents[cursor][idx].first = parents[cursor][idx - 1].first + parents[parents[cursor][idx - 1].second][idx - 1].first;
    }
    
    for (auto& adj : adjL[cursor]) {
    
        if (adj.second != parent) {
            
            initDFS(adj.second, cursor, adj.first);
        }
    }
}

long long LCA(int node1, int node2) {
    
    long long res = 0;
    
    if (height[node1] > height[node2]) {
        
        std::swap(node1, node2);
    }
    
    for (int idx = MAX - 1; idx >= 0; --idx) {
        
        if (height[parents[node2][idx].second] >= height[node1]) {
            
            res += parents[node2][idx].first;
            node2 = parents[node2][idx].second;
        }
    }
    
    if (node1 == node2) {
        
        return res;
    }
    
    for (int idx = MAX - 1; idx >= 0; --idx) {
        
        if (parents[node1][idx].second != parents[node2][idx].second) {
            
            res += parents[node1][idx].first;
            node1 = parents[node1][idx].second;
            
            res += parents[node2][idx].first;
            node2 = parents[node2][idx].second;
        }
    }
    
    return res + parents[node1][0].first + parents[node2][0].first;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx < N; ++idx) {
        
        std::cin >> n1 >> n2 >> d;
        adjL[n1].push_back({d, n2});
        adjL[n2].push_back({d, n1});
    }
    
    initDFS(1, 0, 0);
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> n1 >> n2;
        std::cout << LCA(n1, n2) << '\n';
    }
    
    return 0;
}

