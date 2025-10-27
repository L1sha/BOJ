#include "bits/stdc++.h"


int N, M, K;
std::vector<std::vector<int>> A;
std::vector<std::vector<int>> B;


void matrixMult(){
    
    std::vector<std::vector<int>> res(N);
    
    for (int idx = 0; idx < N; ++idx){
        
        std::vector<int> temp(K, 0);
        for (int idx2 = 0; idx2 < K; ++idx2) {
            
            for (int idx3 = 0; idx3 < M; ++idx3) temp[idx2] += A[idx][idx3] * B[idx3][idx2];
        }
        
        res[idx] = temp;
    }
    
    for (auto& el : res){
        
        for (auto& el2 : el){
            
            std::cout << el2 << ' ';
        }
        
        std::cout << '\n';
    }
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    A.resize(N);
    
    for (auto& el : A){
        
        std::vector<int> temp(M);
        for (auto& el2 : temp) std::cin >> el2;
        el = temp;
    }
    
    std::cin >> M >> K;

    B.resize(M);
    
    for (auto& el : B){
        
        std::vector<int> temp(K);
        for (auto& el2 : temp) std::cin >> el2;
        el = temp;
    }
    
    matrixMult();
    
    return 0;
}


