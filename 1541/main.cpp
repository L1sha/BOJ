#include "bits/stdc++.h"



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::string str;
    std::getline(std::cin, str);
    
    int temp = 0, res = 0;
    bool sw = true;
    
    for (const char& c : str){
        
        if (c == '+') {
            
            if (sw) res += temp;
            else res -= temp;
            
            temp = 0;
        }
        else if (c == '-'){
            
            if (sw) {
                
                res += temp;
                sw = false;
            }
            else res -= temp;
            
            temp = 0;
        }
        else temp = temp * 10 + static_cast<int>(c - '0');
    }
    
    if (sw) res += temp;
    else res -= temp;
    
    std::cout << res;
    
    return 0;
}


