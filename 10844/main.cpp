#include "bits/stdc++.h"


int N;

std::array<std::array<int, 10>, 101> stairs;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx < 10; ++idx) stairs[1][idx] = 1;
    
    for (int idx = 2; idx <= N; ++idx){
        
        stairs[idx][0] = stairs[idx - 1][1];
        for (int idx2 = 1; idx2 <= 8; ++idx2) stairs[idx][idx2] = (stairs[idx - 1][idx2 - 1] + stairs[idx - 1][idx2 + 1]) % 1'000'000'000;
        stairs[idx][9] = stairs[idx - 1][8];
    }
    
    std::cout << std::accumulate(stairs[N].begin(), stairs[N].end(), (long long) 0) % 1'000'000'000;
    
    return 0;
}
