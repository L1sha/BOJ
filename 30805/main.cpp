#include "bits/stdc++.h"


int N, M;

std::array<int, 100> A;
std::array<int, 100> B;






int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> A[idx];
    std::cin >> M;
    for (int idx = 0; idx < M; ++idx) std::cin >> B[idx];
    
    int A_leftIdx = 0, B_leftIdx = 0, A_nextIdx, B_nextIdx, max = 0;
    std::vector<int> res;
    
    while (true) {
        
        max = 0;
        
        for (int aIdx = A_leftIdx; aIdx < N; ++aIdx)
            for (int bIdx = B_leftIdx; bIdx < M; ++bIdx)
                if (A[aIdx] == B[bIdx] && A[aIdx] > max) {
                    
                    max = A[aIdx];
                    A_nextIdx = aIdx + 1;
                    B_nextIdx = bIdx + 1;
                }
                    
        if (!max) break;
        
        A_leftIdx = A_nextIdx;
        B_leftIdx = B_nextIdx;
        
        res.push_back(max);
    }
    
    if (res.empty()) std::cout << 0;
    else {
        
        std::cout << res.size() << '\n';
        for (auto& el : res) std::cout << el << ' ';
    }
    
    return 0;
}


