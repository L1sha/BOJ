#include "bits/stdc++.h"


int N;

std::array<long long, 10001> X;
std::array<long long, 10001> Y;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> X[idx] >> Y[idx];
    
    double res = 0;
    
    for (int idx = 2; idx < N; ++idx){
        
        res += 0.5 * ((X[idx] - X[0]) * (Y[idx - 1] - Y[0]) - (X[idx - 1] - X[0]) * (Y[idx] - Y[0]));
    }
    
    res = std::max(res, -res);
    std::cout << std::fixed;
    std::cout.precision(1);
    
    std::cout << res;
    
    return 0;
}


