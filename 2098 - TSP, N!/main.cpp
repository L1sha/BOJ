#include "bits/stdc++.h"


int N, res = 1e9, temp = 0;

std::array<std::array<int, 16>, 16> adjM;
int visited = 0;    // bitMask

void DFS(int idx){
    
    if (visited == (1 << N) - 1) {
        
        if (adjM[idx][0]) res = std::min(res, temp + adjM[idx][0]);
        
        return;
    }
    
    for (int next = 0; next < N; next++) if (adjM[idx][next] && !((visited >> next) % 2)){
        
        temp += adjM[idx][next];
        visited = visited | (1 << next);
        
        DFS(next);
        
        visited = visited & ~(1 << next);
        temp -= adjM[idx][next];
    }
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < N; ++idx2) std::cin >> adjM[idx][idx2];
    
    visited = 1;
    DFS(0);
    
    std::cout << res;
    
    return 0;
}


