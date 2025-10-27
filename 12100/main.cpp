#include "bits/stdc++.h"


int N, res = 0;

std::array<std::array<int, 21>, 21> board;

int max(){
    
    int max = 0;
    
    for (int idx = 0; idx < N; ++idx) max = std::max(max, *std::max_element(board[idx].begin(), board[idx].begin() + N));
    
    return max;
}

void left(){
    
    for (int idx = 0; idx < N; ++idx){
        
        std::vector<int> compressed;
        int temp = 0;
        
        for (int idx2 = 0; idx2 < N; ++idx2) if (board[idx][idx2]) {
                
            if (temp == board[idx][idx2]){
                
                compressed.push_back(temp * 2);
                temp = 0;
            }
            
            else {
                
                if (temp) compressed.push_back(temp);
                temp = board[idx][idx2];
            }
        }
        if (temp) compressed.push_back(temp);
        
        for (int idx2 = 0; idx2 < compressed.size(); ++idx2) board[idx][idx2] = compressed[idx2];
        for (int idx2 = compressed.size(); idx2 < N; ++idx2) board[idx][idx2] = 0;
    }
}

void right(){
    
    for (int idx = 0; idx < N; ++idx){
        
        std::vector<int> compressed;
        int temp = 0;
        
        for (int idx2 = N - 1; idx2 >= 0; --idx2) if (board[idx][idx2]) {
                
            if (temp == board[idx][idx2]){
                
                compressed.push_back(temp * 2);
                temp = 0;
            }
            
            else {
                
                if (temp) compressed.push_back(temp);
                temp = board[idx][idx2];
            }
        }
        if (temp) compressed.push_back(temp);

        for (int idx2 = N - 1; idx2 >= N - (int)compressed.size(); --idx2) {
            board[idx][idx2] = compressed[N - 1 - idx2];
        }
        for (int idx2 = N - 1 - (int)compressed.size(); idx2 >= 0; --idx2) board[idx][idx2] = 0;
    }
}

void up(){
    
    for (int idx = 0; idx < N; ++idx){
        
        std::vector<int> compressed;
        int temp = 0;
        
        for (int idx2 = 0; idx2 < N; ++idx2) if (board[idx2][idx]) {
                
            if (temp == board[idx2][idx]){
                
                compressed.push_back(temp * 2);
                temp = 0;
            }
            
            else {
                
                if (temp) compressed.push_back(temp);
                temp = board[idx2][idx];
            }
        }
        if (temp) compressed.push_back(temp);
        
        for (int idx2 = 0; idx2 < compressed.size(); ++idx2) board[idx2][idx] = compressed[idx2];
        for (int idx2 = compressed.size(); idx2 < N; ++idx2) board[idx2][idx] = 0;
    }
}

void down(){
    
    for (int idx = 0; idx < N; ++idx){
        
        std::vector<int> compressed;
        int temp = 0;
        
        for (int idx2 = N - 1; idx2 >= 0; --idx2) if (board[idx2][idx]) {
                
            if (temp == board[idx2][idx]){
                
                compressed.push_back(temp * 2);
                temp = 0;
            }
            
            else {
                
                if (temp) compressed.push_back(temp);
                temp = board[idx2][idx];
            }
        }
        if (temp) compressed.push_back(temp);

        for (int idx2 = N - 1; idx2 >= N - (int)compressed.size(); --idx2) {
        
            board[idx2][idx] = compressed[N - 1 - idx2];
        }
        for (int idx2 = N - 1 - (int)compressed.size(); idx2 >= 0; --idx2) board[idx2][idx] = 0;
    }
}


void solve(int num){
    
    if (num == 0) { res = std::max(res, max()); return; }

    std::array<std::array<int, 21>, 21> temp;
    temp = board;
    
    left();
    solve(num - 1);
    board = temp;
    
    right();
    solve(num - 1);
    board = temp;
    
    up();
    solve(num - 1);
    board = temp;
    
    down();
    solve(num - 1);
    board = temp;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < N; ++idx2) std::cin >> board[idx][idx2];
    
    solve(5);
    
    std::cout << res;
    
    return 0;
}


