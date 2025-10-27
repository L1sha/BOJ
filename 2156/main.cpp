#include "bits/stdc++.h"


int N;

std::array<int, 10'001> OO;
std::array<int, 10'001> OX;
std::array<int, 10'001> XO;
std::array<int, 10'001> XX;




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int temp;
    
    std::cin >> N >> XO[0];
    
    if (N == 1) std::cout << XO[0];
    else {
        
        std::cin >> XO[1];
        OO[1] = XO[1] + XO[0];
        OX[1] = XO[0];
        
        for (int idx = 2; idx < N; ++idx){
            
            std::cin >> temp;
            OO[idx] = XO[idx - 1] + temp;
            OX[idx] = std::max(XO[idx - 1], OO[idx - 1]);
            XO[idx] = std::max(XX[idx - 1], OX[idx - 1]) + temp;
            XX[idx] = std::max(XX[idx - 1], OX[idx - 1]);
        }
        
        std::cout << std::max(std::max(OO[N - 1], XO[N - 1]), OX[N - 1]);
    }
    
    
    return 0;
}



