#include "bits/stdc++.h"


int N;

std::array<bool, 15> row;
std::array<bool, 15> col;
std::array<bool, 30> diag;
std::array<bool, 30> diag2;
std::array<std::array<bool, 15>, 15> queen;

int numQueen = 0, res = 0, rIdx = 0;

void NQueen() {
    
    if (rIdx == N) {
        
        res++;
        return;
    }
    
    for (int cIdx = 0; cIdx < N; ++cIdx){
        
        if (!col[cIdx] && !diag[rIdx + cIdx] && !diag2[rIdx + N - 1 - cIdx]){
            
            col[cIdx] = true;
            diag[rIdx + cIdx] = true;
            diag2[rIdx + N - 1 - cIdx] = true;
            rIdx++;
            
            NQueen();
            
            rIdx--;
            col[cIdx] = false;
            diag[rIdx + cIdx] = false;
            diag2[rIdx + N - 1 - cIdx] = false;
        }
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    NQueen();
    
    std::cout << res;
    
    return 0;
}


