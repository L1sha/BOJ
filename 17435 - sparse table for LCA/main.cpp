#include "bits/stdc++.h"


constexpr int m_MAX = 200'001;
constexpr int logN_MAX = std::ceil(std::log2(500'000)) + 1;

int M, Q, N, X, pow2;
std::array<std::array<int, logN_MAX>, m_MAX> sparseTable;
std::array<int, m_MAX> F;




int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> M;
    
    for (int idx = 1; idx <= M; ++idx) {
        
        std::cin >> sparseTable[idx][0];
    }
    
    for (int idx = 1; idx < logN_MAX; ++idx) {
        
        for (int idx2 = 1; idx2 <= M; ++idx2) {
            
            sparseTable[idx2][idx] = sparseTable[sparseTable[idx2][idx - 1]][idx - 1];
        }
    }
    
    std::cin >> Q;
    
    while (Q--) {
        
        pow2 = 0;
        
        std::cin >> N >> X;
        
        while (N) {
            
            if (N % 2) {
                
                X = sparseTable[X][pow2];
            }
            
            pow2++;
            N /= 2;
        }
        
        std::cout << X << '\n';
    }
     
    return 0;
}

