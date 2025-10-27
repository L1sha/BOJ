#include "bits/stdc++.h"

long long X1, Y1, X2, Y2, X3, Y3, X4, Y4;
const long long zero = 0;

std::tuple<bool, bool, long double, long double> cross(long long X1, long long Y1, long long X2, long long Y2, long long X3, long long Y3, long long X4, long long Y4) {
    
    bool res = false, onepoint = false;
    long double xOrigin = 0, yOrigin = 0, x = 0, y = 0;
    
    if (X1 > X2) { std::swap(X1, X2); std::swap(Y1, Y2); } 
    
    X2 -= X1;   // X2 >= 0
    X3 -= X1;
    X4 -= X1;
    Y2 -= Y1;
    Y3 -= Y1;
    Y4 -= Y1;
    xOrigin += X1;
    yOrigin += Y1;
    X1 = 0;
    Y1 = 0;
    
    long long a = Y2, b = - X2; // P1, P2 : ax + by = 0
    
    long long judge3 = a * X3 + b * Y3, judge4 = a * X4 + b * Y4;
    
    if (!judge3 && !judge4) {   //  both P3 & P4 are on the line
        
        if (X2 == 0){   // line x = 0
            
            if (Y2 > 0) {
                
                if (Y3 == 0) {
                    
                    res = true;
                    
                    if (Y4 < 0) {
                        
                        onepoint = true;
                        x = 0;
                        y = 0;
                    }
                }
                else if (Y3 == Y2) {
                    
                    res = true;
                    
                    if (Y4 > Y2) {
                        
                        onepoint = true;
                        x = 0;
                        y = Y2;
                    }
                }
                else if (Y3 > 0 && Y3 < Y2) {
                    
                    res = true;
                }
                else if (Y3 < 0) {
                    
                    if (Y4 >= 0) {
                        
                        res = true;
                        
                        if (Y4 == 0) {
                            
                            onepoint = true;
                            x = 0;
                            y = 0;
                        }
                    }
                }
                else {      // if (Y3 > Y2)
                    
                    if (Y4 <= Y2) {
                        
                        res = true;
                        
                        if (Y4 == Y2) {
                            
                            onepoint = true;
                            x = 0;
                            y = Y2;
                        }
                    }
                }
            }
            else {      // if (Y2 < 0)
                
                if (Y3 == 0) {
                    
                    res = true;
                    
                    if (Y4 > 0) {
                        
                        onepoint = true;
                        x = 0;
                        y = 0;
                    }
                }
                else if (Y3 == Y2) {
                    
                    res = true;
                    
                    if (Y4 < Y2) {
                        
                        onepoint = true;
                        x = 0;
                        y = Y2;
                    }
                }
                else if (Y3 < 0 && Y3 > Y2) {
                    
                    res = true;
                }
                else if (Y3 > 0) {
                    
                    if (Y4 <= 0) {
                        
                        res = true;
                        
                        if (Y4 == 0) {
                            
                            onepoint = true;
                            x = 0;
                            y = 0;
                        }
                    }
                }
                else {      // if (Y3 < Y2)
                    
                    if (Y4 >= Y2) {
                        
                        res = true;
                        
                        if (Y4 == Y2) {
                            
                            onepoint = true;
                            x = 0;
                            y = Y2;
                        }
                    }
                }
            }
        }
        else {      // if (X2 > 0)
            
            if (X3 == 0) {
                
                res = true;
                
                if (X4 < 0) {
                    
                    onepoint = true;
                    x = 0;
                    y = 0;
                }
            }
            else if (X3 == X2) {
                
                res = true;
                
                if (X4 > X2) {
                    
                    onepoint = true;
                    x = X2;
                    y = Y2;
                }
            }
            else if (X3 > 0 && X3 < X2) {
                
                res = true;
            }
            else if (X3 < 0) {
                
                if (X4 >= 0) {
                    
                    res = true;
                    
                    if (X4 == 0) {
                        
                        onepoint = true;
                        x = 0;
                        y = 0;
                    }
                }
            }
            else {  // if (X3 > X2)
                
                if (X4 <= X2) {
                    
                    res = true;
                    
                    if (X4 == X2) {
                        
                        onepoint = true;
                        x = X2;
                        y = Y2;
                    }
                }
            }
        }
    }
    else if (!judge3 || !judge4) {       // only one of P3 & P4 is on the line
        
        if (!judge4) { std::swap(X3, X4); std::swap(Y3, Y4); }  // P3 is on the line
        
        if (X2 == 0) {  // line x = 0
            
            if (Y3 >= std::min(zero, Y2) && Y3 <= std::max(zero, Y2)) {
                
                res = true;
                onepoint = true;
                x = X1;
                y = Y1 + Y3;
            }
        }
        else {  // if (X2 > 0)
            
            if (X3 >= 0 && X3 <= X2) {
                
                res = true;
                onepoint = true;
                x = X1 + X3;
                y = Y1 + Y3;
            }
        }
    }
    else if ((judge3 > 0 && judge4 < 0) || (judge3 < 0 && judge4 > 0)) {    // P3, P4 is on different side
        
        if (X3 > X4) { std::swap(X3, X4); std::swap(Y3, Y4); }
        X4 -= X3; // X4 >= 0
        X1 -= X3;
        X2 -= X3;
        Y4 -= Y3;
        Y1 -= Y3;
        Y2 -= Y3;
        xOrigin += X3;
        yOrigin += Y3;
        X3 = 0;
        Y3 = 0;
        
        long long c = Y4, d = -X4; // P3, P4 : cx + dy = 0
        
        long long judge1 = c * X1 + d * Y1, judge2 = c * X2 + d * Y2;
        
        // NOTE: judge1 & judge2 cannot be zero at the same time (because judge3 != 0 & judge4 != 0)
        if (!judge1 || !judge2) {   // one of P1, P2 is on the line
            
            res = true;
            onepoint = true;
            
            if (!judge2) { std::swap(X1, X2); std::swap(Y1, Y2); }  // P1 is on the line
            
            x = X1;
            y = Y1;
        }
        else if ((judge1 > 0 && judge2 < 0) || (judge1 < 0 && judge2 > 0)) {     // P1, P2 is on different side
            
            res = true;
            onepoint = true;
            
            if (X4 == 0) {      // P3, P4 : line x = 0
                
                x = 0;
                y = Y1 + (Y2 - Y1) * (-X1) / ((long double)(X2 - X1));
            }
            else if (X1 == X2) {    // P1, P2 : line x = X1
                
                x = X1;
                y = Y4 * X1 / ((long double)X4);
            }
            else {
                
                long double a = (Y2 - Y1) / ((long double)(X2 - X1));
                long double b = Y1 - a * X1;     // P1, P2 : line y = ax + b
                long double c = Y4 / ((long double)X4); // P3, P4 : line y = cx
                
                x = b / (c - a);
                y = c * x;
            }
        }
    }
    
    x += xOrigin;
    y += yOrigin;

    return {res, onepoint, x, y};
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3 >> X4 >> Y4;
    
    std::cout << std::fixed;
    std::cout.precision(16);
    
    auto [res, onepoint, x, y] = cross(X1, Y1, X2, Y2, X3, Y3, X4, Y4);
    if (res) {
        
        std::cout << 1;
        if (onepoint) {
            
            std::cout << '\n'<< x << ' ' << y;
        }
    }
    else {
        
        std::cout << 0;
    }
    
    return 0;
}