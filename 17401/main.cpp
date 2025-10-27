#include "bits/stdc++.h"


using Mat = std::array<std::array<long long, 21>, 21>;

int T, N, D, M, A, B, C;
const int PRIME = 1'000'000'007;

std::array<Mat, 101> maps;
Mat res;

Mat matMult(const Mat& m1, const Mat& m2) {
    
    Mat temp;
    
    for (auto& row : temp) {
        
        std::fill(row.begin(), row.end(), 0);
    }
    
    for (int row = 1; row <= N; ++row) {
        
        for (int col = 1; col <= N; ++col) {
            
            for (int idx = 1; idx <= N; ++idx) {
                
                temp[row][col] += m1[row][idx] * m2[idx][col];
                temp[row][col] %= PRIME;
            }
        }
    }
    
    return temp;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T >> N >> D;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        res[idx][idx] = 1;
        maps[0][idx][idx] = 1;
    }
    
    for (int idx = 1; idx <= T; ++idx) {
        
        std::cin >> M;
        while (M--) {
            
            std::cin >> A >> B >> C;
            maps[idx][A][B] = C;
        }
        
        maps[idx] = matMult(maps[idx - 1], maps[idx]);
    }
    
    int expo = D / T;
    
    while (expo) {
        
        if (expo % 2) {
            
            res = matMult(res, maps[T]);
        }
        
        expo /= 2;
        maps[T] = matMult(maps[T], maps[T]);
    }
    
    res = matMult(res, maps[D % T]);
    
    for (int row = 1; row <= N; ++row) {
        
        for (int col = 1; col <= N; ++col) {
            
            std::cout << res[row][col] << ' ';
        }
        std::cout << '\n';
    }
    
    return 0;
}

