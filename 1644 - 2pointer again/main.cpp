#include "bits/stdc++.h"


long long N;

std::array<int, 4'000'001> isPrime;
std::vector<int> primes;

void fillPrime() {
    
    std::fill(isPrime.begin() + 2, isPrime.end(), true);
    
    for (int idx = 2; idx < 4'000'001; ++idx) if (isPrime[idx]) {
        
        for (int idx2 = idx; idx2 < 4'000'001; idx2 += idx) isPrime[idx2] = false;
        primes.push_back(idx);
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    fillPrime();
     
    int cnt = 0;
    
    int temp = 0;
    auto left = primes.begin(), right = primes.begin();
    
    while (true) {
        
        if (temp <= N) {
            
            if (temp == N) cnt++;
            if (right == primes.end()) break;
            temp += *right++;
        }
        else {
            
            temp -= *left++;
            if (left == right) break;
        }
    }
    
    std::cout << cnt;
    
    return 0;
}




