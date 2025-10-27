#include "bits/stdc++.h"


int N, cursor = 0;
bool solved = false;

std::array<std::array<int, 9>, 9> board;
std::vector<std::pair<int, int>> blanks;

void printBoard(){
    
    for (const auto& el : board) {
        
        for (const auto& el2 : el) std::cout << el2 << ' ';
        std::cout << '\n';
    }
}

bool rowAvailable(int num, int rIdx){
    
    for (int idx = 0; idx < 9; ++idx) if (board[rIdx][idx] == num) return false;
    return true;
}

bool colAvailable(int num, int cIdx){
    
    for (int idx = 0; idx < 9; ++idx) if (board[idx][cIdx] == num) return false;
    return true;
}

bool boxAvailable(int num, int bIdx){
    
    for (int rIdx = 0; rIdx < 3; ++rIdx) for (int cIdx = 0; cIdx < 3; ++cIdx) if (board[rIdx + (bIdx / 3) * 3][cIdx + (bIdx % 3) * 3] == num) return false;
    return true;
}

void solve(){
    
    if (solved) return;
    
    if (cursor == N) {
        
        solved = true;
        printBoard();
        return;
    }
    
    int rIdx = blanks[cursor].first, cIdx = blanks[cursor].second;
    
    for (int num = 1; num <= 9; ++num) if (rowAvailable(num, rIdx) && colAvailable(num, cIdx) && boxAvailable(num, (rIdx / 3) * 3 + (cIdx / 3))) {
        
        board[rIdx][cIdx] = num;
        cursor++;
        solve();
        if (solved) return;
        cursor--;
        board[rIdx][cIdx] = 0;
    }
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    for (int rIdx = 0; rIdx < 9; ++rIdx) for (int cIdx = 0; cIdx < 9; ++cIdx) {
            
        std::cin >> board[rIdx][cIdx];
        if (board[rIdx][cIdx] == 0) blanks.push_back(std::make_pair(rIdx, cIdx));
    }
    
    N = blanks.size();
    
    solve();
    
    
    return 0;
}


