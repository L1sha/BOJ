#include "bits/stdc++.h"


int sz;
const long long PRIME = 1'000'000'007;

std::string s;
std::array<long long, 2501> memo;
std::array<long long, 2501> power;



void solve(int right) {
    
    long long forward = 0, backward = 0, min = 1e9;
    
    for (int idx = 0; idx < right; ++idx) {
        
        forward = ((forward * 26) + s[right - idx - 1] - 'A') % PRIME;
        backward = (backward + power[idx] * (s[right - idx - 1] - 'A')) % PRIME;
        if (forward == backward) min = std::min(memo[right - idx - 1] + 1, min);
    }
    
    memo[right] = min;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> s;
    sz = s.size();
    
    power[0] = 1;
    for (int idx = 1; idx <= 2500; ++idx) power[idx] = (power[idx - 1] * 26) % PRIME;
    
    for (int idx = 1; idx <= sz; ++idx) solve(idx);
    
    std::cout << memo[sz];
    
    return 0;
}

