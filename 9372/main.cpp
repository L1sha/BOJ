#include "bits/stdc++.h"


int T, M, N;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> N >> M;
        std::cout << N - 1 << '\n';
        while (M--) std::cin >> N >> N;
    }
    
    return 0;
}

