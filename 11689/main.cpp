#include "bits/stdc++.h"


long long N, res;
int sz;

std::array<bool, 1'000'001> isPrime;
std::vector<int> primeSet;
std::vector<long long> divisorSet;
std::vector<int> s;



void findPrime() {
    
    std::fill(isPrime.begin() + 2, isPrime.end(), true);
    
    for (int num = 2; num <= 1'000'000; ++num) {
        
        if (isPrime[num]) {
            
            for (int toDelete = num * 2; toDelete <= 1'000'000; toDelete += num) {
                
                isPrime[toDelete] = false;
            }
            
            primeSet.push_back(num);
        }
    }
}

void solve(const int& num, int cursor) {
    
    if (s.size() == num) {
        
        long long divisor = 1;
        for (auto& el : s) divisor *= divisorSet[el];
        
        res -= ((num % 2) * 2 - 1) * (N / divisor);
        
        return;
    }
    
    if (s.size() + sz - cursor < num) {
        
        return;
    }
    
    for (int idx = cursor; idx < sz; ++idx) {
        
        s.push_back(idx);
        
        solve(num, idx + 1);
        
        s.pop_back();
    }
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    findPrime();
    
    std::cin >> N;
    
    long long temp = N;
    
    for (auto& el : primeSet) {
        
        if (temp % el == 0) {
            
            divisorSet.push_back(el);
            
            while (temp % el == 0) {
                
                temp /= el;
            }
        }
    }
    
    if (temp != 1) {
        
        divisorSet.push_back(temp);
    }
    
    res = N;
    sz = divisorSet.size();
    
    for (int idx = 1; idx <= sz; ++idx) {
        
        solve(idx, 0);
    }
    
    std::cout << res;
    
    return 0;
}

