#include "bits/stdc++.h"


int N;
std::array<int, 100'001> hasNthNum;
std::array<int, 100'001> noNthNum;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int temp;
    
    std::cin >> N >> temp;
    if (N == 1) std::cout << temp;
    else {
        
        hasNthNum[0] = temp;
        noNthNum[0] = -1234567890;
    
        for (int idx = 1; idx < N; ++idx){
            
            std::cin >> temp;
            
            if (hasNthNum[idx - 1] < 0) hasNthNum[idx] = temp;
            else hasNthNum[idx] = temp + hasNthNum[idx - 1];
            
            noNthNum[idx] = hasNthNum[idx - 1] > noNthNum[idx - 1] ? hasNthNum[idx - 1] : noNthNum[idx - 1]; 
        }
        
        noNthNum[N] = hasNthNum[N - 1] > noNthNum[N - 1] ? hasNthNum[N - 1] : noNthNum[N - 1];
        
        std::cout << noNthNum[N];
    }
    return 0;
}


