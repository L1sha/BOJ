#include "bits/stdc++.h"


int N;
std::array<std::string, 3072> res;

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int multiplier = 1;
    
    while (multiplier != N) {
        
        if (multiplier == 1) {
            
            res[N - 3] = "  *   ";
            res[N - 2] = " * *  ";
            res[N - 1] = "***** ";
            
            multiplier = 3;
        }
        else {
            
            for (int idx = 1; idx <= multiplier; ++idx) {
                
                res[N - multiplier - idx] += std::string(multiplier, ' ');
                res[N - multiplier - idx] += res[N - idx];
                res[N - multiplier - idx] += std::string(multiplier, ' ');
                
                res[N - idx] += res[N - idx];
            }
            
            multiplier *= 2;
        }
    }
    
    for (int idx = 0; idx < N; ++idx) std::cout << res[idx] << '\n';
    
    return 0;
}


