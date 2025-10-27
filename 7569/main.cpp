#include "bits/stdc++.h"


struct tomato {
    
    int h, row, col;
    tomato() = default;
    tomato(int h, int row, int col) : h(h), row(row), col(col) {}
};

int N, M, H;

std::array<std::array<std::array<int, 100>, 100>, 100> tomatoes;
std::array<std::array<std::array<bool, 100>, 100>, 100> visited;

bool isAvailable(int h, int row, int col) {
    
    if (h < 0 || row < 0 || col < 0) return false;
    if (h >= H || row >= N || col >= M) return false;
    if (visited[h][row][col]) return false;
    if (tomatoes[h][row][col]) return false;
    return true;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> M >> N >> H;
    
    std::vector<tomato> welldone, next;
    
    for (int h = 0; h < H; ++h) for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) {
        
        std::cin >> tomatoes[h][row][col];
        if (tomatoes[h][row][col] == 1) welldone.push_back({h, row, col});
    }
    
    int res = 0;
    
    while (true) {
        
        for (auto &el : welldone) {
            
            if (isAvailable(el.h - 1, el.row, el.col)) {
                
                next.push_back({el.h - 1, el.row, el.col});
                visited[el.h - 1][el.row][el.col] = true;
            }
            if (isAvailable(el.h + 1, el.row, el.col)) {
                
                next.push_back({el.h + 1, el.row, el.col});
                visited[el.h + 1][el.row][el.col] = true;
            }
            if (isAvailable(el.h, el.row - 1, el.col)) {
                
                next.push_back({el.h, el.row - 1, el.col});
                visited[el.h][el.row - 1][el.col] = true;
            }
            if (isAvailable(el.h, el.row + 1, el.col)) {
                
                next.push_back({el.h, el.row + 1, el.col});
                visited[el.h][el.row + 1][el.col] = true;
            }
            if (isAvailable(el.h, el.row, el.col - 1)) {
                
                next.push_back({el.h, el.row, el.col - 1});
                visited[el.h][el.row][el.col - 1] = true;
            }
            if (isAvailable(el.h, el.row, el.col + 1)){
                
                next.push_back({el.h, el.row, el.col + 1});
                visited[el.h][el.row][el.col + 1] = true;
            }
        }
        
        if (next.empty()) break;
        res++;
        welldone = next;
        next.clear();
    }
    
    for (int h = 0; h < H; ++h) for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) {
        
        if (tomatoes[h][row][col] == 0 && !visited[h][row][col]) {
            
            std::cout << -1;
            return 0;
        }
    }
    
    std::cout << res;    
    
    return 0;
}

