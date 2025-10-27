#include "bits/stdc++.h"


int N, plus, zero, minus;

std::vector<std::vector<int>> input;


int solve(int size, int row, int col){
    
    if (size == 1) {
        
        switch(input[row][col]){
            
            case -1:
            minus++;
            break;
            
            case 0:
            zero++;
            break;
            
            case 1:
            plus++;
            break;
        }
        
        return input[row][col];
    }
    
    std::array<std::array<int, 3>, 3> sub;
    for (int rIdx = 0; rIdx < 3; ++rIdx) for (int cIdx = 0; cIdx < 3; ++cIdx) sub[rIdx][cIdx] = solve(size / 3, row * 3 + rIdx, col * 3 + cIdx);
    
    int res = sub[0][0];
    
    for (int rIdx = 0; rIdx < 3; ++rIdx) for (int cIdx = 0; cIdx < 3; ++cIdx) if (sub[rIdx][cIdx] != sub[0][0] || sub[rIdx][cIdx] == -2) return -2;
    
    switch(res){
        
        case -1:
        minus -= 8;
        return -1;
        
        case 0:
        zero -= 8;
        return 0;
        
        case 1:
        plus -= 8;
        return 1;
    }
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int temp;
    std::vector<int> vectorTemp(N, 0);
    
    for (int rIdx = 0; rIdx < N; ++rIdx){
        
        for (auto& el : vectorTemp) std::cin >> el;
        input.push_back(vectorTemp);
    }
    
    solve(N, 0, 0);
    
    std::cout << minus << '\n' << zero << '\n' << plus;
    
    return 0;
}


