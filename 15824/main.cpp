#include "bits/stdc++.h"


int N;
const long long PRIME = 1'000'000'007;

std::array<int, 300'000> Scoville;
std::array<int, 300'000> powerOf2; 




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    std::cin >> Scoville[0];
    powerOf2[0] = 1;
    
    for (int idx = 1; idx < N; ++idx) {
        
        std::cin >> Scoville[idx];
        powerOf2[idx] = (powerOf2[idx - 1] * 2) % PRIME;
    }
    
    std::sort(Scoville.begin(), Scoville.begin() + N);
    
    int res = 0;
    
    for (int idx = 0; idx < N; ++idx) {
        
        res = (res + (Scoville[idx] % PRIME) * powerOf2[idx]) % PRIME;
        res = (res + (PRIME - Scoville[idx] % PRIME) * powerOf2[N - 1 - idx]) % PRIME;
    }
    
    std::cout << res;
    
    return 0;
}

