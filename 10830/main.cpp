#include "bits/stdc++.h"


int N;
long long B;

using Matrix = std::vector<std::vector<int>>;

Matrix matMult(const Matrix& A, const Matrix& B){
    
    Matrix res{N};
    for (int row = 0; row < N; ++row){
        
        res[row].resize(N, 0);
        
        for (int col = 0; col < N; ++col) {
            
            for (int idx = 0; idx < N; ++idx) res[row][col] += A[row][idx] * B[idx][col];
            res[row][col] %= 1000;
        }
    }
    
    return res;
}

void matExp(const Matrix& A, long long B){
    
    Matrix temp(A), res{N};
    for (int idx = 0; idx < N; ++idx){
        
        res[idx].resize(N, 0);
        res[idx][idx] = 1;
    }
    
    while (B != 0){
        
        if (B % 2 == 1) res = matMult(res, temp);
        
        B /= 2;
        temp = matMult(temp, temp);
    }
    
    for (auto& el : res){
        
        for (auto& el2 : el) std::cout << el2 << ' ';
        std::cout << '\n';
    }
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> B;
    
    Matrix A{N};
    for (auto& el : A) {
        
        el.resize(N);
        for (auto& el2 : el) std::cin >> el2;
    }
    
    matExp(A, B);
    
    return 0;
}


