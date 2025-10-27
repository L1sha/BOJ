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
    
    bool connected;
       
    for (int idx = 1; idx <= N; ++idx) for (int idx2 = 1; idx2 <= N; ++idx2) {
        
        std::cin >> connected;
        
        if (connected) Union(idx, idx2);
    }
    
    int cursor, next;
    std::cin >> cursor;
    
    while (--M) {
        
        std::cin >> next;
        if (getParent(cursor) != getParent(next)) {
            
            std::cout << "NO";
            return 0;
        }
        
        cursor = next;
    }
    
    std::cout << "YES";
    return 0;
}

