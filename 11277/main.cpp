#include "bits/stdc++.h"


int N, M;
std::array<std::pair<int, int>, 100> clauses;
std::bitset<21> TF;

bool check(int idx) {
    
    if (clauses[idx].first < 0) {
        
        if (!TF[-clauses[idx].first]) {
            
            return true;
        }
    }
    else {
        
        if (TF[clauses[idx].first]) {
            
            return true;
        }
    }
    
    if (clauses[idx].second < 0) {
        
        if (!TF[-clauses[idx].second]) {
            
            return true;
        }
    }
    else {
        
        if (TF[clauses[idx].second]) {
            
            return true;
        }
    }
    
    return false;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> clauses[idx].first >> clauses[idx].second;
    }
    
    int temp, cursor;
    bool res;
    
    for (int bitMask = 0; bitMask < (1 << N); ++bitMask) {
        
        temp = bitMask;
        cursor = 1;
        TF.reset();
        res = true;
        
        while (temp) {
            
            if (temp & 1) {
                
                TF[cursor] = true;
            }
            
            temp >>= 1;
            cursor++;
        }
        
        for (int idx = 0; idx < M; ++idx) {
            
            if (!check(idx)) {
                
                res = false;
                break;
            }
        }
        
        if (res) {
            
            std::cout << 1;
            return 0;
        }
    }
    
    std::cout << 0;
    
    return 0;
}

