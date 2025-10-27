#include "bits/stdc++.h"


int N = 2;
long long n;

const int PRIME = 1'000'000'007;

using Matrix = std::vector<std::vector<long long>>;

Matrix matMult(const Matrix& A, const Matrix& B){
    
    Matrix res{N};
    for (int row = 0; row < N; ++row){
        
        res[row].resize(N, 0);
        
        for (int col = 0; col < N; ++col) {
            
            for (int idx = 0; idx < N; ++idx) res[row][col] = (res[row][col] + A[row][idx] * B[idx][col]) % PRIME;
        }
    }
    
    return res;
}

void matExp(const Matrix& A, long long n){
    
    Matrix temp(A), res{N};
    for (int idx = 0; idx < N; ++idx){
        
        res[idx].resize(N, 0);
        res[idx][idx] = 1;
    }
    
    while (n != 0){
        
        if (n % 2 == 1) res = matMult(res, temp);
        
        n /= 2;
        temp = matMult(temp, temp);
    }
    
    std::cout << res[1][0];
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> n;
    
    Matrix A{2};
    A[0] = {1, 1};
    A[1] = {1, 0};
    
    matExp(A, n);
    
    return 0;
}


