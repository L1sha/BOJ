#include "bits/stdc++.h"


int R, C, T;

std::array<std::array<int, 50>, 50> map;
std::array<std::array<int, 50>, 50> temp;
int machine;


void spread() {
    
    temp = map;
    for (int row = 0; row < R; ++row)
        for (int col = 0; col < C; ++col)
            if (temp[row][col] > 0) {
                
                int spreaded = temp[row][col] / 5;
                if (!spreaded) continue;
                
                if (row - 1 >= 0 && map[row - 1][col] != -1) {
                    
                    map[row - 1][col] += spreaded;
                    map[row][col] -= spreaded;
                }
                if (row + 1 < R && map[row + 1][col] != -1) {
                    
                    map[row + 1][col] += spreaded;
                    map[row][col] -= spreaded;
                }
                if (col - 1 >= 0 && map[row][col - 1] != -1) {
                    
                    map[row][col - 1] += spreaded;
                    map[row][col] -= spreaded;
                }
                if (col + 1 < C && map[row][col + 1] != -1) {
                    
                    map[row][col + 1] += spreaded;
                    map[row][col] -= spreaded;
                }
            }
}


void clean() {
    
    for (int row = machine - 2; row >= 1; --row) map[row][0] = map[row - 1][0];
    for (int col = 0; col < C - 1; ++col) map[0][col] = map[0][col + 1];
    for (int row = 0; row < machine - 1; ++row) map[row][C - 1] = map[row + 1][C - 1];
    for (int col = C - 1; col >= 2; --col) map[machine - 1][col] = map[machine - 1][col - 1];
    map[machine - 1][1] = 0;
    
    for (int row = machine + 1; row < R - 1; ++row) map[row][0] = map[row + 1][0];
    for (int col = 0; col < C - 1; ++col) map[R - 1][col] = map[R - 1][col + 1];
    for (int row = R - 1; row > machine; --row) map[row][C - 1] = map[row - 1][C - 1];
    for (int col = C - 1; col >= 2; --col) map[machine][col] = map[machine][col - 1];
    map[machine][1] = 0;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> R >> C >> T;
    for (int row = 0; row < R; ++row)
        for (int col = 0; col < C; ++col) {
            
            std::cin >> map[row][col];
            if (map[row][col] == -1) machine = row;
        }
    
    while (T--) {
        
        spread();
        clean();
    }
    
    int res = 2;
    
    for (int row = 0; row < R; ++row)
        for (int col = 0; col < C; ++col) 
            res += map[row][col];
    
    std::cout << res;
    
    return 0;
}


