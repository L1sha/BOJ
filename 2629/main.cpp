#include "bits/stdc++.h"


int N, K;

std::array<bool, 40001> res;
std::array<int, 30> weight;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> weight[idx];
    
    res[0] = true;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::vector<int> toAdd;
        
        for (int idx2 = weight[idx]; idx2 <= 40000; ++idx2) {
            
            if (res[idx2 - weight[idx]] && !res[idx2]) toAdd.push_back(idx2);
        }
        
        for (auto &el : toAdd) res[el] = true;
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::vector<int> toAdd;
        
        for (int idx2 = 40000 - weight[idx]; idx2 >= 0; --idx2) {
            
            if (res[idx2 + weight[idx]] && !res[idx2]) toAdd.push_back(idx2);
        }
        
        for (auto &el : toAdd) res[el] = true;
    }
    
    std::cin >> K;
    while (K--) {
        
        std::cin >> N;
        if (res[N]) std::cout << "Y ";
        else std::cout << "N ";
    }
    
    return 0;
}

