#include "bits/stdc++.h"

const long long DIVIDER = 1'000'000;

long long N;

using mat = std::array<std::array<long long, 2>, 2>;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
}

mat matMult(const mat& A, const mat& B) {
    
    mat res;
    
    for (int row = 0; row < 2; ++row) {
        
        for (int col = 0; col < 2; ++col) {
            
            res[row][col] = 0;
            
            for (int mid = 0; mid < 2; ++mid) {
                
                res[row][col] += A[row][mid] * B[mid][col];
                res[row][col] %= DIVIDER;
            }
        }
    }
    
    return res;
}

void solve() {
    
    mat res{{
        
        {1, 0},
        {0, 1}
    }};
    
    mat multiplier{{
        
        {1, 1},
        {1, 0}
    }};
    
    while (N) {
        
       if (N % 2) {
           
           res = matMult(res, multiplier);
       } 
       
       multiplier = matMult(multiplier, multiplier);
       N /= 2;
    }
    
    std::cout << res[1][0];
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

