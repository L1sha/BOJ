#include "bits/stdc++.h"


int D;
const int PRIME = 1'000'000'007;

std::vector<std::vector<long long>> res;
std::vector<std::vector<long long>> mat;

std::vector<std::vector<long long>> mult(const std::vector<std::vector<long long>>& a, const std::vector<std::vector<long long>>& b) {
    
    std::vector<std::vector<long long>> res(a.size(), std::vector<long long>(b[0].size(), 0));
    
    for (int row = 0; row < a.size(); ++row) {
        
        for (int col = 0; col < b[0].size(); ++col) {
            
            for (int idx = 0; idx < b.size(); ++idx) {
                
                res[row][col] = (res[row][col] + a[row][idx] * b[idx][col]) % PRIME;
            }
        }
    }
    
    return res;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> D;
    
    res.resize(8, std::vector<long long>(1, 0));
    mat.resize(8, std::vector<long long>(8));
    res[0][0] = 1;
    
    mat = {
        {0,1,1,0,0,0,0,0},
        {1,0,1,1,0,0,0,0},
        {1,1,0,1,1,0,0,0},
        {0,1,1,0,1,1,0,0},
        {0,0,1,1,0,1,1,0},
        {0,0,0,1,1,0,0,1},
        {0,0,0,0,1,0,0,1},
        {0,0,0,0,0,1,1,0}
    };
    
    while (D) {
        
        if (D % 2) res = mult(mat, res);
        mat = mult(mat, mat);
        D /= 2;
    }
    
    std::cout << res[0][0];
    
    return 0;
}

