#include "bits/stdc++.h"


int N;

std::array<std::array<std::string, 64>, 64> input;

std::string merge(int size, int row, int col){
    
    if (size == 1) return input[row][col];
    
    std::array<std::string, 4> sub;
    for (int idx = 0; idx < 4; ++idx) sub[idx] = merge(size / 2, row * 2 + idx / 2, col * 2 + idx % 2);
    
    std::string one = "1";
    std::string zero = "0";
    
    if (sub[0] == one && sub[1] == one && sub[2] == one && sub[3] == one) return one;
    if (sub[0] == zero && sub[1] == zero && sub[2] == zero && sub[3] == zero) return zero;
    
    std::string res = "(";
    for (const auto& el : sub) res += el;
    res += ")";
    return res;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    std::string temp;
    for (int rIdx = 0; rIdx < N; ++rIdx) {
        
        std::cin >> temp;
        for (int cIdx = 0; cIdx < N; ++cIdx) input[rIdx][cIdx] = temp[cIdx];
    }
    
    std::cout << merge(N, 0, 0);
    
    return 0;
}


