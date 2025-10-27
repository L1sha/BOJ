#include "bits/stdc++.h"


int N, r, c;

std::array<int, 16> Exp2;




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    Exp2[0] = 1; 
    for (int idx = 1; idx < 16; ++idx) Exp2[idx] = Exp2[idx - 1] * 2;
    
    std::cin >> N >> r >> c;
    
    int res = 0;
    
    while (N--){
        
        res += Exp2[N] * Exp2[N] * (r / Exp2[N] * 2 + c / Exp2[N]);
        r %= Exp2[N];
        c %= Exp2[N];
    }
    
    std::cout << res;
    
    return 0;
}


