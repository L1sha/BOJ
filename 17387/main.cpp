#include "bits/stdc++.h"

long long X1, Y1, X2, Y2, X3, Y3, X4, Y4;
long long zero = 0;
int res;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3 >> X4 >> Y4;
    
    if (X1 > X2) { std::swap(X1, X2); std::swap(Y1, Y2); } 
    
    X2 -= X1;   // X2 >= 0
    X3 -= X1;
    X4 -= X1;
    Y2 -= Y1;
    Y3 -= Y1;
    Y4 -= Y1;
    X1 = 0;
    Y1 = 0;
    
    long long a = Y2, b = - X2; // P1, P2 : ax + by = 0
    
    long long judge3 = a * X3 + b * Y3, judge4 = a * X4 + b * Y4;
    
    if (!judge3 && !judge4) {   //  both P3 & P4 are on the line
        
        if (X2 == 0){   // line x = 0
            
            if ((Y3 >= std::min(zero, Y2) && Y3 <= std::max(zero, Y2)) || (Y4 >= std::min(zero, Y2) && Y4 <= std::max(zero, Y2))) res = 1;
            
            else if ((Y3 < std::min(zero, Y2) && Y4 > std::max(zero, Y2)) || (Y3 > std::max(zero, Y2) && Y4 < std::min(zero, Y2))) res = 1;
            
            else res = 0;
        }
        
        else {      // X2 > 0
            
            if ((X3 >= 0 && X3 <= X2) || (X4 >= 0 && X4 <= X2)) res = 1;
            
            else if ((X3 < 0 && X4 > X2) || (X3 > X2 && X4 < 0)) res = 1;
            
            else res = 0;
        }
        
    }
    
    else if (!judge3 || !judge4) {       // only one of P3 & P4 is on the line
        
        if (!judge4) { std::swap(X3, X4); std::swap(Y3, Y4); }  // P3 is on the line
        
        if (X2 == 0) {  // line x = 0
            
            if (Y3 >= std::min(zero, Y2) && Y3 <= std::max(zero, Y2)) res = 1;
            
            else res = 0;
        }
        
        else {  // X2 > 0
            
            if (X3 >= 0 && X3 <= X2) res = 1;
            
            else res = 0;
        }
    }
    
    else if ((judge3 > 0 && judge4 > 0) || (judge3 < 0 && judge4 < 0)) res = 0;     // P3, P4 is on same side
    
    else {  // P3, P4 is on different side
        
        if (X3 > X4) { std::swap(X3, X4); std::swap(Y3, Y4); }
        X4 -= X3; // X4 >= 0
        X1 -= X3;
        X2 -= X3;
        Y4 -= Y3;
        Y1 -= Y3;
        Y2 -= Y3;
        X3 = 0;
        Y3 = 0;
        
        long long c = Y4, d = -X4; // P3, P4 : cx + dy = 0
        
        long long judge1 = c * X1 + d * Y1, judge2 = c * X2 + d * Y2;
        
        if ((judge1 > 0 && judge2 > 0) || (judge1 < 0 && judge2 < 0)) res = 0;      // P1, P2 is on same side
        
        else res = 1;
    }

    std::cout << res;    
    
    return 0;
}


