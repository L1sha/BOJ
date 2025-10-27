#include "bits/stdc++.h"


int N, K;
const int PRIME = 1'000'000'003;

std::array<std::array<int, 1001>, 501> OO;
std::array<std::array<int, 1001>, 501> OX;
std::array<std::array<int, 1001>, 501> XO;
std::array<std::array<int, 1001>, 501> XX;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    if (K > N / 2) {
        
        std::cout << 0;
        return 0;
    }
    
    std::fill(XX[0].begin(), XX[0].begin() + N + 1, 1);
    OO[1][1] = 1;
    
    for (int k = 1; k <= K; ++k) {
        
        for (int idx = 2; idx <= N; ++idx) {
            
            OO[k][idx] = OX[k - 1][idx - 1];
            OX[k][idx] = (OO[k][idx - 1] + OX[k][idx - 1]) % PRIME;
            XO[k][idx] = XX[k - 1][idx - 1];
            XX[k][idx] = (XO[k][idx - 1] + XX[k][idx - 1]) % PRIME;
        }
    }
    
    /*
    for (int k = 0; k <= K; ++k) {
        for (int idx = 0; idx <= N; ++idx){
            
            std::cout << OO[k][idx] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    for (int k = 0; k <= K; ++k) {
        for (int idx = 0; idx <= N; ++idx){
            
            std::cout << OX[k][idx] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    for (int k = 0; k <= K; ++k) {
        for (int idx = 0; idx <= N; ++idx){
            
            std::cout << XO[k][idx] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    for (int k = 0; k <= K; ++k) {
        for (int idx = 0; idx <= N; ++idx){
            
            std::cout << XX[k][idx] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    */
    
    std::cout << ((OX[K][N] + XO[K][N]) % PRIME + XX[K][N]) % PRIME;
    
    return 0;
}

