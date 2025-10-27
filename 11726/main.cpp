#include "bits/stdc++.h"


int N;

std::array<int, 1001> fibo;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    fibo[0] = 1;
    fibo[1] = 1;
    for (int idx = 2; idx <= N; ++idx) fibo[idx] = (fibo[idx - 1] + fibo[idx - 2]) % 10'007;
    
    std::cout << fibo[N];
    
    return 0;
}


