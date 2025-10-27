#include "bits/stdc++.h"


int N, M;

std::vector<std::vector<int>> partyPeople;
std::vector<bool> redDrug;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    redDrug.resize(N + 1, false);
    partyPeople.resize(M);
    
    int num, temp;
    
    std::cin >> num;
    while (num--) {
        
        std::cin >> temp;
        redDrug[temp] = true;
    }
    
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> num;
        partyPeople[idx].resize(num);
        for (auto& el : partyPeople[idx]) std::cin >> el;
    }
    
    std::vector<bool> revealed(M, false);
    
    for (int repeat = 0; repeat < M; ++repeat) {
        
        for (int party = 0; party < M; ++party) if (!revealed[party]) {
            
            for (auto& el : partyPeople[party]) if (redDrug[el]) {
                
                revealed[party] = true;
                break;
            }
            
            if (revealed[party]) for (auto& el : partyPeople[party]) redDrug[el] = true;
        }
    }
    
    std::cout << std::count(revealed.begin(), revealed.end(), false);
    
    return 0;
}


