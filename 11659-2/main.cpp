#include "bits/stdc++.h"


int N, M, ql, qr;
std::array<int, 100'001> partial;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> partial[1];
    
    int temp;
    
    for (int idx = 2; idx <= N; ++idx){
        
        std::cin >> temp;
        partial[idx] = partial[idx - 1] + temp;
    }
    
    while (M--) {
        
        std::cin >> ql >> qr;
        std::cout << partial[qr] - partial[ql - 1] << '\n';
    }
    
    return 0;
}


