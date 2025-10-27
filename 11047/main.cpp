#include "bits/stdc++.h"


int N, K;





int main(int argc, char* *argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    std::vector<int> coins(N);
    for (auto& el: coins) std::cin >> el;
    std::sort(coins.begin(), coins.end(), std::greater<int>());
    
    int idx = 0, res = 0;
    
    while (K != 0){
        
        if (coins[idx] <= K){
            
            K -= coins[idx];
            res++;
        }
        else idx++;
    }
    
    std::cout << res;
    
    return 0;
}



