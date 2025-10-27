#include "bits/stdc++.h"


int N;

std::array<int, 41> fibo0;
std::array<int, 41> fibo1;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    fibo0[0] = 1;
    fibo0[1] = 0;
    fibo1[0] = 0;
    fibo1[1] = 1;
    for (int idx = 2; idx < 41; ++idx) { fibo0[idx] = fibo0[idx - 1] + fibo0[idx - 2]; fibo1[idx] = fibo1[idx - 1] + fibo1[idx - 2]; }
    
    int temp;
    
    while (N--){
        
        std::cin >> temp;
        std::cout << fibo0[temp] << ' ' << fibo1[temp] << '\n';
    }
    
    
    
    return 0;
}


