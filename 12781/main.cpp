#include "bits/stdc++.h"

long long X1, Y1, X2, Y2, X3, Y3, X4, Y4;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3 >> X4 >> Y4;
}

void solve() {
    
    //    (Y2 - Y1)(x - X1) - (X2 - X1)(y - Y1) = 0
    
    long long a = Y2 - Y1, b = X1 - X2, c = - (Y2 - Y1) * X1 + (X2 - X1) * Y1;
    
    long long det3 = a * X3 + b * Y3 + c, det4 = a * X4 + b * Y4 + c;
    
    if ((det3 > 0 && det4 < 0) || (det3 < 0 && det4 > 0)) std::cout << 1;
    else std::cout << 0;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}