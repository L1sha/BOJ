#include "bits/stdc++.h"

int N, T;
std::array<std::optional<long long>, 101> fibo;

long long pado(int N){
    
    if (fibo[N].has_value()) return fibo[N].value();
    else {
        
        fibo[N] = pado(N - 1) + pado(N - 5);
        return fibo[N].value();
    }
}

int main(){
    
    std::cin >> T;
    
    fibo[0] = 1;
    fibo[1] = 1;
    fibo[2] = 1;
    fibo[3] = 1;
    fibo[4] = 2;
    fibo[5] = 2;
    
    while (T--){
        
        std::cin >> N;
        
        std::cout << pado(N) << '\n';
    }
    
    return 0;
}
