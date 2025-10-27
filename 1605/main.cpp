#include "bits/stdc++.h"


constexpr int L_MAX = 200'000;
const long long PRIME = 26, PRIME1 = 1e9 + 7, PRIME2 = 1e9 + 9;

int L;
std::string S;

bool check(int length) {
    
    std::unordered_set<int> set1, set2;
    set1.reserve(L - length + 1);
    set2.reserve(L - length + 1);
    
    int check1 = 0, check2 = 0;
    long long pow1 = 1, pow2 = 1;
    
    for (int idx = 0; idx < length; ++idx) {
        
        check1 = (check1 * PRIME + S[idx] % 26) % PRIME1;
        check2 = (check2 * PRIME + S[idx] % 26) % PRIME2;
        pow1 = (pow1 * PRIME) % PRIME1;
        pow2 = (pow2 * PRIME) % PRIME2;
    }
    
    set1.insert(check1);
    set2.insert(check2);
    
    for (int idx = 1; idx <= L - length; ++idx) {
        
        check1 = (check1 * PRIME - (S[idx - 1] % 26) * pow1 + 26 * PRIME1 + S[idx + length - 1] % 26) % PRIME1;
        check2 = (check2 * PRIME - (S[idx - 1] % 26) * pow2 + 26 * PRIME2 + S[idx + length - 1] % 26) % PRIME2;
        
        if (set1.count(check1) && set2.count(check2)) return true;
        
        set1.insert(check1);
        set2.insert(check2);
    }
    
    return false;
}

int solve() {
    
    int l = 0, r = L, mid;
    
    while (r - l > 1) {
        
        mid = (l + r) / 2;
        
        if (check(mid)) {
            
            l = mid;
        }
        else {
            
            r = mid;
        }
    }
    
    return l;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> L >> S;
    
    std::cout << solve();
    
    return 0;
}

