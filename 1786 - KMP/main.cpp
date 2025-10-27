#include "bits/stdc++.h"


int N;

std::string T, P;
std::array<int, 1'000'001> KMP;



void init() {
    
    int corrected = 0;
    
    KMP[0] = 0;
    KMP[1] = 0;
    
    for (int idx = 2; idx <= P.size(); ++idx) {
        
        if (P[corrected] == P[idx - 1]) {
            
            KMP[idx] = ++corrected;
        }
        else if (corrected) {
            
            corrected = KMP[corrected];
            idx--;
        }
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::getline(std::cin, T);
    std::getline(std::cin, P);
    
    if (T.size() < P.size()) {
        
        std::cout << 0;
        return 0;
    }
    
    init();
    
    int corrected = 0, cnt = 0;
    std::vector<int> res;
    
    for (int idx = 0; idx < T.size(); ++idx) {
        
        if (T[idx] == P[corrected]) {
            
            corrected++;
            
            if (corrected == P.size()) {
                
                cnt++;
                res.push_back(idx - corrected + 2);
                
                corrected = KMP[corrected];
            }
        }
        else if (corrected) {
            
            corrected = KMP[corrected];
            idx--;
        }
    }
    
    std::cout << cnt << '\n';
    for (auto& el : res) std::cout << el << ' ';
    
    return 0;
}

