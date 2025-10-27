#include "bits/stdc++.h"


// IDEA : sum (1e6 / n; n = 1 ~ 1e6) = 13970034


int N;

std::array<int, 100'001> players; // <num, idx>;
std::array<int, 100'001> res;
std::array<int, 1'000'001> doesExist;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> players[idx];
        doesExist[players[idx]] = idx;
    }
    
    for (int idx = 1; idx <= 1'000'000; ++idx) if (doesExist[idx]) {
        
        for (int idx2 = 2 * idx; idx2 <= 1'000'000; idx2 += idx) if (doesExist[idx2]) {
            
            res[doesExist[idx]]++;
            res[doesExist[idx2]]--;
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) std::cout << res[idx] << ' ';
    
    return 0;
}


