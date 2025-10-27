#include "bits/stdc++.h"


int N, M;
std::vector<int> stak;

void DFS(int remaining){
    
    if (remaining == 0){
        
        for (auto &el : stak) std::cout << el << ' ';
        std::cout << '\n';
        return;
    }
    
    for (int next = (stak.empty() ? 1 : stak.back()); next <= N; ++next) {
        
        stak.push_back(next);
        DFS(remaining - 1);
        stak.pop_back();
    }
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    DFS(M);
    
    return 0;
}




