#include <iostream>
#include <string>

int main() {
    
    int T;
    std::cin >> T;
    
    if (T == 1) {
        
        long long A, B, sum;
        std::cin >> A >> B;
        sum = A + B;
        
        for (int idx = 0; idx < 13; ++idx) {
            
            std::cout << static_cast<char>(static_cast<int>('a') + sum % 26);
            sum /= 26;
        }
        
        std::cout << std::endl;
    }
    else {
        
        long long res = 0;
        std::string s;
        std::cin >> s;
        
        for (long long idx = 0, base = 1; idx < 13; ++idx) {
            
            res += (static_cast<int>(s[idx]) - static_cast<int>('a')) * base;
            base *= 26;
        }
        
        std::cout << res << std::endl;
    }
    
    return 0;
}