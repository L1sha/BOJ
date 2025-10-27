#include "bits/stdc++.h"


int N, M, command, a, b;
std::array<int, 1'000'001> parent;

int getParent(int idx) {
    
    if (parent[idx] != idx) return parent[idx] = getParent(parent[idx]);
    return idx;
}

void Union(int idx1, int idx2) {
    
    parent[getParent(idx2)] = getParent(idx1);
}




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) parent[idx] = idx;
    
    while (M--) {
        
        std::cin >> command >> a >> b;
        
        if (command) {
            
            if (getParent(a) == getParent(b)) std::cout << "YES\n";
            else std::cout << "NO\n";
        }
        else Union(a, b);
    }
    
    return 0;
}

