#include "bits/stdc++.h"


int V, E;

std::array<std::pair<int, std::pair<int, int>>, 100'001> edges;
std::array<int, 10'001> myParent;

int getParent(int idx){
    
    if (idx != myParent[idx]) return myParent[idx] = getParent(myParent[idx]);
    return idx;
}

void Union(int idx1, int idx2){
    
    myParent[getParent(idx2)] = getParent(idx1);
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> V >> E;
    
    int from, to, weight;
    
    for (int idx = 0; idx < E; ++idx){
        
        std::cin >> from >> to >> weight;
        edges[idx] = {weight, {from, to}};
    }
    
    std::sort(edges.begin(), edges.begin() + E);
    
    int res = 0, cnt = 1;
    
    for (int idx = 1; idx <= V; ++idx) myParent[idx] = idx;
    
    if (V != 1) for (int idx = 0; idx < E; ++idx){
        
        auto temp = edges[idx];
        
        if (getParent(temp.second.first) != getParent(temp.second.second)){
            
            res += temp.first;
            Union(temp.second.first, temp.second.second);
            
            if (++cnt == V) break;
        }
    }
    
    std::cout << res;
    
    return 0;
}



