#include "bits/stdc++.h"


long long A, B;

long long solve(long long num) {
    
    long long temp = num, res = 0, power = 1;
    std::vector<int> binary;
    
    while (temp) {
        
        binary.push_back(temp % 2);
        temp /= 2;
        power *= 2;
    }
    
    for (int idx = binary.size() - 1; idx >= 0; --idx) {
        
        power /= 2;
        
        if (binary[idx]) {
            
            num -= power;
            res += (num + 1);
            res += idx * (power / 2);
        }
    }
    
    return res;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> A >> B;
    
    std::cout << solve(B) - solve(A - 1);
    
    return 0;
}

