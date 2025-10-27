#include "bits/stdc++.h"


long long N;

std::array<int, 4'000'001> isPrime;
std::vector<long long> partialSum;

void fillPrime() {
    
    std::fill(isPrime.begin() + 2, isPrime.end(), true);
    
    partialSum.push_back(0);
    
    for (int idx = 2; idx < 4'000'001; ++idx) if (isPrime[idx]) {
        
        for (int idx2 = idx; idx2 < 4'000'001; idx2 += idx) isPrime[idx2] = false;
        partialSum.push_back(partialSum.back() + idx);
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    fillPrime();
     
    int cnt = 0;
    
    for (auto it = std::lower_bound(partialSum.begin(), partialSum.end(), N); it != partialSum.end(); ++it) {
        
        if (*it - *(it - 1) > N) break;
        
        auto it2 = std::lower_bound(partialSum.begin(), partialSum.end(), *it - N);
        if (*it2 == *it - N) ++cnt;
    }
    
    std::cout << cnt;
    
    return 0;
}



