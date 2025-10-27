#include "bits/stdc++.h"


long long P, Q, D;

long long GCD(long long A, long long B) {
    
    return B ? GCD(B, A % B) : A;
}

long long solve() {
    
    if (D % P == 0 || D % Q == 0) return D;
    if (P == Q) return (D / P + 1) * P;
    
    if (P < Q) std::swap(P, Q);     // Now, P > Q
    
    long long res = INT_MAX;
        
    for (long long idx = 0, maxIdx = Q / GCD(P, Q), temp; idx < maxIdx; ++idx) {
        
        if ((temp = D - idx * P) < 0) {
            
            res = std::min(res, P * idx);
            break;
        }
        
        if (temp % Q) res = std::min(res, P * idx + (temp / Q + 1) * Q);
        else return D;
    }
    
    return res;
}



int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> D >> P >> Q;
    
    std::cout << solve();
    
    return 0;
}

