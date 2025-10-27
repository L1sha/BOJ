#include "bits/stdc++.h"

/*

f(n) = f(n - 2) + 2g(n - 1)
g(n) = f(n - 1) + g(n - 2)

=> f(n + 1) - f(n - 1) = 2f(n - 1) + f(n - 1) - f(n - 3)
f(n + 1) = 4f(n - 1) - f(n - 3)
f(n + 4) = 4f(n + 2) - f(n), f(0) = 1, f(2) = 3

n = 2k, f'(k) = f(2k) -> f'(k + 2) = 4f'(k + 1) - f'(k), f'(0) = 1, f'(1) = 3

  f'(k + 2)       4   -1      f'(k + 1)
[           ] = [        ]  [           ]
  f'(k + 1)       1   0         f'(k)

*/

long long N;

const long long PRIME = 1'000'000'007;

using Mat = std::array<std::array<long long, 2>, 2>;

Mat matMult(const Mat& A, const Mat& B) {
    
    Mat res;
    
    for (int row = 0; row < 2; ++row) {
        
        for (int col = 0; col < 2; ++col) {
            
            res[row][col] = 0;
            
            for (int idx = 0; idx < 2; ++idx) {
                
                res[row][col] += A[row][idx] * B[idx][col];
            }
            
            res[row][col] %= PRIME;
        }
    }
    
    return res;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    if (N & 1) {
        
        std::cout << 0;
        
        return 0;
    }
    
    N >>= 1;
    
    Mat mult, res;
    mult[0] = {4, PRIME - 1};
    mult[1] = {1, 0};
    res[0] = {1, 0};
    res[1] = {0, 1};
    
    while (N) {
        
        if (N & 1) {
            
            res = matMult(res, mult);
        }
        
        mult = matMult(mult, mult);
        
        N >>= 1;
    }
    
    std::cout << (3 * res[1][0] + res[1][1]) % PRIME;
    
    return 0;
}


