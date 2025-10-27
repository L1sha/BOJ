#include <iostream>
#include <array>

std::array<int, 1'000'001> fibo;

int main(){
    
    int N;
    std::cin >> N;
    
    fibo[0] = 1;
    fibo[1] = 1;
    
    if (N >= 2){
        
        for (int idx = 2; idx <= N; ++idx) fibo[idx] = (fibo[idx - 1] + fibo[idx - 2]) % 15746;
    }
    std::cout << fibo[N];
    
    return 0;
}
