#include "bits/stdc++.h"


int a, b, c;
std::array<std::array<std::array<std::optional<int>, 21>, 21>, 21> memo;

int w(int a, int b, int c){
    
    if (a <= 0 || b <= 0 || c <= 0) return 1;
    if (a > 20 || b > 20 || c > 20) return w(20, 20, 20);
    
    if (memo[a][b][c].has_value()) return memo[a][b][c].value();
    
    if (a < b && b < c){
        
        memo[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
        return memo[a][b][c].value();
    }
    else {
        
        memo[a][b][c] = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
        return memo[a][b][c].value();
    }
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    while (true){
        
        std::cin >> a >> b >> c;
        if (a == -1 && b == -1 && c == -1) break;
        
        std::cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << '\n';
    }
    
    return 0;
}


