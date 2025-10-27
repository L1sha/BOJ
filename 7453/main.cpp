#include "bits/stdc++.h"


int N;

std::array<int, 4001> A;
std::array<int, 4001> B;
std::array<int, 4001> C;
std::array<int, 4001> D;
std::array<int, 16008001> AB;
std::array<int, 16008001> CD;




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> A[idx] >> B[idx] >> C[idx] >> D[idx];
    
    int cursor = 0;
    for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < N; ++idx2){
        
        AB[cursor] = A[idx] + B[idx2];
        CD[cursor++] = C[idx] + D[idx2];
    }
    
    std::sort(CD.begin(), CD.begin() + N * N );
    
    long long res = 0;
    
    for (int idx = 0; idx < N * N; ++idx) {
        
        auto it = std::equal_range(CD.begin(), CD.begin() + N * N, -AB[idx]);
        res += std::distance(it.first, it.second);
    }
    
    std::cout << res;
    
    return 0;
}


