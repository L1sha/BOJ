#include "bits/stdc++.h"


int T, N;

std::array<std::array<int, 100'001>, 2> sticker;
std::array<int, 100'001> OX;
std::array<int, 100'001> XO;
std::array<int, 100'001> XX;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--){
        
        std::cin >> N;
        
        for (int idx2 = 0; idx2 < 2; ++idx2) for (int idx = 0; idx < N; ++idx) std::cin >> sticker[idx2][idx];
        
        OX[0] = sticker[0][0];
        XO[0] = sticker[1][0];
        XX[0] = 0;
        
        for (int idx = 1; idx < N; ++idx){
            
            OX[idx] = std::max(XO[idx - 1], XX[idx - 1]) + sticker[0][idx];
            XO[idx] = std::max(OX[idx - 1], XX[idx - 1]) + sticker[1][idx];
            XX[idx] = std::max(std::max(OX[idx - 1], XO[idx - 1]), XX[idx - 1]);
        }
        
        std::cout << std::max(OX[N - 1], XO[N - 1]) << '\n';
    }
    
    return 0;
}


