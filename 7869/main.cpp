#include "bits/stdc++.h"


using LD = long double;

LD X1, Y1, R1, X2, Y2, R2;
const LD PI = 3.141592653589793238462643383279502884L;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cout << std::fixed;
    std::cout.precision(3);
    
    std::cin >> X1 >> Y1 >> R1 >> X2 >> Y2 >> R2;
    
    if (R1 > R2) {
        
        std::swap(X1, X2);
        std::swap(Y1, Y2);
        std::swap(R1, R2);
    }
    
    LD dist = sqrtl(powl(X1 - X2, 2) + powl(Y1 - Y2, 2)), res = 0;
    
    if (dist <= R2 - R1) {
        
        res = PI * R1 * R1;
    }
    else if (dist <= R2 + R1) {
        
        LD angle;
        
        angle = acosl((dist * dist + R1 * R1 - R2 * R2) / (2 * dist * R1));
        res += (0.5 * R1 * R1 * angle - 0.5 * R1 * R1 * cosl(angle) * sinl(angle)) * 2;
        
        angle = acosl((dist * dist + R2 * R2 - R1 * R1) / (2 * dist * R2));
        res += (0.5 * R2 * R2 * angle - 0.5 * R2 * R2 * cosl(angle) * sinl(angle)) * 2;
    }
    
    std::cout << res;
    
    return 0;
}

