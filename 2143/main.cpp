#include "bits/stdc++.h"


// cnt can be long long fxxk

int T, N, M;

std::array<int, 1000> A;
std::array<int, 500'500> allA;
std::array<int, 1000> B;
std::array<int, 500'500> allB;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T >> N;
    
    int sizeA = 0, sizeB = 0, temp;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> A[idx];
        temp = A[idx];
        allA[sizeA++] = temp;
        for (int idx2 = idx - 1; idx2 >= 0; --idx2) {
            
            temp += A[idx2];
            allA[sizeA++] = temp;
        }
    }
    
    std::cin >> M;
    
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> B[idx];
        temp = B[idx];
        allB[sizeB++] = temp;
        for (int idx2 = idx - 1; idx2 >= 0; --idx2) {
            
            temp += B[idx2];
            allB[sizeB++] = temp;
        }
    }
    
    std::sort(allB.begin(), allB.begin() + sizeB);
    
    long long cnt = 0;
    
    for (int idx = 0; idx < sizeA; ++idx) {
        
        auto pair = std::equal_range(allB.begin(), allB.begin() + sizeB, T - allA[idx]);
        cnt += std::distance(pair.first, pair.second);
    }
    
    std::cout << cnt;
    
    return 0;
}


