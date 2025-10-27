#include "bits/stdc++.h"


using LD = long double;

LD X, Y, D, T;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cout << std::fixed;
    std::cout.precision(16);
    
    std::cin >> X >> Y >> D >> T;
    
    LD dist = sqrtl(X * X + Y * Y), res = 0;
    
    if (D <= T) {
        
        res = dist;   
    }
    else if (dist > D) {
        
        while (true) {
            
            if (dist < 2 * D) {
                
                dist -= D;
                
                LD toAdd = T + std::min(dist, T + D - dist);
                toAdd = std::min(toAdd, 2 * T);
                
                res += toAdd;
                
                break;
            }
            
            dist -= D;
            res += T;
        }
    }
    else {
        
        res = std::min(dist, T + D - dist);
        res = std::min(res, 2 * T);
    }
    
    std::cout << res;
    
    return 0;
}

