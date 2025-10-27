#include "bits/stdc++.h"


int N;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int previous, target, max = 0;
    std::string res;
    
    while (N--){
        
        std::cin >> target;
        if (max < target) {
            
            while (max != target){
            
                max++;
                res += '+';
            }
            res += '-';
        }
        else if (previous = target + 1) res += '-';
        else { std::cout << "NO"; return 0; }
        
        previous = target;
    }
    
    for (auto& el : res) std::cout << el << '\n';
    
    return 0;
}


