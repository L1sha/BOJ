#include "bits/stdc++.h"


int R, C, max = 0;

std::array<std::array<char, 20>, 20> board;
std::array<int, 26> alphabet;

void solve(int row, int col, int num) {
    
    alphabet[board[row][col] - 'A']++;
    
    if (row - 1 >= 0 && !alphabet[board[row - 1][col] - 'A']) solve(row - 1, col, num + 1);
    if (row + 1 < R && !alphabet[board[row + 1][col] - 'A']) solve(row + 1, col, num + 1);
    if (col - 1 >= 0 && !alphabet[board[row][col - 1] - 'A']) solve(row, col - 1, num + 1);
    if (col + 1 < C && !alphabet[board[row][col + 1] - 'A']) solve(row, col + 1, num + 1);
    
    alphabet[board[row][col] - 'A']--;
    
    max = std::max(num, max);
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> R >> C;
    
    for (int row = 0; row < R; ++row) for (int col = 0; col < C; ++col) std::cin >> board[row][col];
    
    solve(0, 0, 1);
    
    std::cout << max;
    
    return 0;
}


