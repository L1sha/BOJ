#include "bits/stdc++.h"


int N, M;

std::array<int, 500'001> parent;

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
    
    for (int idx = 0; idx <= N - 1; ++idx) parent[idx] = idx;
    
    int flag = 0, A, B;
    
    for (int idx = 1; idx <= M; ++idx) {
        
        std::cin >> A >> B;
        
        if (flag) continue;
        
        if (getParent(A) == getParent(B)) {
            
            flag = idx;
            continue;
        }
        
        Union(A, B);
    }
    
    std::cout << flag;
    
    return 0;
}



