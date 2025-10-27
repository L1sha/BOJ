#include "bits/stdc++.h"


long long X1, X2, X3, Y1, Y2, Y3;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3;
    
    X3 -= X2;
    Y3 -= Y2;
    X2 -= X1;
    Y2 -= Y1;
    
    long long res = X2 * Y3 - X3 * Y2;
    
    if (res > 0) res = 1;
    else if (res < 0) res = -1;
    
    std::cout << res;
    
    return 0;
}

