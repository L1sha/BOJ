#include "bits/stdc++.h"


int G, P;

std::array<int, 100'001> parent;

int getParent(int idx) {
    
    if (idx != parent[idx]) return parent[idx] = getParent(parent[idx]);
    return idx;
}

void Union(int idx1, int idx2) {
    
    parent[getParent(idx2)] = getParent(idx1);
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> G >> P;
    
    for (int idx = 1; idx <= G; ++idx) parent[idx] = idx;
    
    int cnt = 0, g, temp;
    while (P--) {
        
        std::cin >> g;
        temp = getParent(g);
        if (!temp) break;
        Union(temp - 1, temp);
        cnt++;
    }
    
    std::cout << cnt;
    
    return 0;
}

