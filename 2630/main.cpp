#include "bits/stdc++.h"


int N, white, blue;

int check(const std::vector<std::vector<int>>& colors, int row, int col){
    
    int color = colors[2 * row][2 * col];
    
    for (int rowIdx = 2 * row; rowIdx < 2 * (row + 1); ++rowIdx)
    for (int colIdx = 2 * col; colIdx < 2 * (col + 1); ++colIdx)
    if (colors[rowIdx][colIdx] != color || colors[rowIdx][colIdx] == -1) return -1;
    
    if (color) blue -= 3;
    else white -= 3;
    
    return color;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int size = 1, cursor = 0;
    
    std::vector<std::vector<std::vector<int>>> colors;
    
    colors.push_back({N, std::vector<int>(N, 0)});
    for (auto& el : colors[0]) for (auto& el2 : el) { std::cin >> el2; blue += el2; }
    white = N * N - blue;
    
    while (N != 1){
        
        N /= 2;
        cursor += 1;
        
        colors.push_back({N, std::vector<int>(N, 0)});
        for (int rIdx = 0; rIdx < N; ++rIdx)
        for (int cIdx = 0; cIdx < N; ++cIdx) colors[cursor][rIdx][cIdx] = check(colors[cursor - 1], rIdx, cIdx);
    }
    
    std::cout << white << '\n' << blue;
    
    return 0;
}


