#include "bits/stdc++.h"


int A, B, C;

std::unordered_map<int, int> memo;

long long power(int A, int B, int C){
    
    if (memo.count(B)) return memo[B];
    
    int res;
    
    res = (power(A, B / 2, C) * power(A, B - B / 2, C)) % C;
    memo[B] = res;
    return res;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> A >> B >> C;
    
    memo[1] = A % C;
    
    std::cout << power(A % C, B, C);
    
    return 0;
}


