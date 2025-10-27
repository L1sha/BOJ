#include "bits/stdc++.h"

constexpr int R_MAX = 25, C_MAX = 25 ;

int R, C, cnt = 0, sRow, sCol;

std::vector<std::vector<char>> map;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> R >> C;
    
    map.resize(R, std::vector<char>(C));
    
    for (auto& row : map) {
        
        for (auto& el : row) {
            
            std::cin >> el;
            
            if (el != '.') {
                
                ++cnt;
                
                if (el == 'M') {
                    
                    sRow = &row - &map.front();
                    sCol = &el - &row.front();
                }
                else if (el == '+') ++cnt;
            }
        }
    }
}

bool solve(int cRow = sRow, int cCol = sCol, int cCnt = 0, int dir = 0) {
    
    if (map[cRow][cCol] == 'Z') {
        
        if (cCnt == cnt) return true;
        else return false;
    }
    
    if (dir == 0) {
        
        if (cCol + 1 < C) {
            
            if (map[cRow][cCol + 1] == '-' || map[cRow][cCol + 1] == '+' || 
                map[cRow][cCol + 1] == '3' || map[cRow][cCol + 1] == '4') {
                    
                return solve(cRow, cCol + 1, cCnt + 1, 1);
            }
        }
        
        if (cRow - 1 >= 0) {
            
            if (map[cRow - 1][cCol] == '|' || map[cRow - 1][cCol] == '+' || 
                map[cRow - 1][cCol] == '1' || map[cRow - 1][cCol] == '4') {
                    
                return solve(cRow - 1, cCol, cCnt + 1, 2);
            }
        }
        
        if (cCol - 1 >= 0) {
            
            if (map[cRow][cCol - 1] == '-' || map[cRow][cCol - 1] == '+' || 
                map[cRow][cCol - 1] == '1' || map[cRow][cCol - 1] == '2') {
                    
                return solve(cRow, cCol - 1, cCnt + 1, 3);
            }
        }
        
        if (cRow + 1 < R) {
            
            if (map[cRow + 1][cCol] == '|' || map[cRow + 1][cCol] == '+' || 
                map[cRow + 1][cCol] == '2' || map[cRow + 1][cCol] == '3') {
                    
                return solve(cRow + 1, cCol, cCnt + 1, 4);
            }
        }
        
        if (cCol + 1 < C) {
            
            if (solve(cRow, cCol + 1, cCnt + 1, 1)) return true;
        }
        
        if (cRow - 1 >= 0) {
            
            if (solve(cRow - 1, cCol, cCnt + 1, 2)) return true;
        }
        
        if (cCol - 1 >= 0) {
            
            if (solve(cRow, cCol - 1, cCnt + 1, 3)) return true;
        }
        
        if (cRow + 1 < R) {
            
            if (solve(cRow + 1, cCol, cCnt + 1, 4)) return true;
        }
    }
    else if (dir == 1) {
        
        if (map[cRow][cCol] == '.') {
            
            if (cCol + 1 < C && map[cRow][cCol + 1] != '.') {
                
                map[cRow][cCol] = '-';
                if (solve(cRow, cCol + 1, cCnt + 1, 1)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '-';
                    return true;
                }
                
                map[cRow][cCol] = '+';
                ++cnt;
                if (solve(cRow, cCol + 1, cCnt + 1, 1)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '+';
                    return true;
                }
                --cnt;
            }
            
            if (cRow - 1 >= 0 && map[cRow - 1][cCol] != '.') {
                
                map[cRow][cCol] = '3';
                if (solve(cRow - 1, cCol, cCnt + 1, 2)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '3';  
                    return true;
                }
            }
            
            if (cRow + 1 < R && map[cRow + 1][cCol] != '.') {
                
                map[cRow][cCol] = '4';
                if (solve(cRow + 1, cCol, cCnt + 1, 4)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '4'; 
                    return true;
                }
            }
            
            map[cRow][cCol] = '.';
            return false;
        }
        else if (map[cRow][cCol] == '-') {
            
            return solve(cRow, cCol + 1, cCnt + 1, 1);
        }
        else if (map[cRow][cCol] == '+') {
            
            return solve(cRow, cCol + 1, cCnt + 1, 1);
        }
        else if (map[cRow][cCol] == '3') {
            
            return solve(cRow - 1, cCol, cCnt + 1, 2);
        }
        else if (map[cRow][cCol] == '4') {
            
            return solve(cRow + 1, cCol, cCnt + 1, 4);
        }
    }
    else if (dir == 2) {
        
        if (map[cRow][cCol] == '.') {
            
            if (cRow - 1 >= 0 && map[cRow - 1][cCol] != '.') {
                
                map[cRow][cCol] = '|';
                if (solve(cRow - 1, cCol, cCnt + 1, 2)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '|';
                    return true;
                }
                
                map[cRow][cCol] = '+';
                ++cnt;
                if (solve(cRow - 1, cCol, cCnt + 1, 2)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '+';
                    return true;
                }
                --cnt;
            }
            
            if (cCol - 1 >= 0 && map[cRow][cCol - 1] != '.') {
                
                map[cRow][cCol] = '4';
                if (solve(cRow, cCol - 1, cCnt + 1, 3)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '4';  
                    return true;
                }
            }
            
            if (cCol + 1 < C && map[cRow][cCol + 1] != '.') {
                
                map[cRow][cCol] = '1';
                if (solve(cRow, cCol + 1, cCnt + 1, 1)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '1'; 
                    return true;
                }
            }
            
            map[cRow][cCol] = '.';
            return false;
        }
        else if (map[cRow][cCol] == '|') {
            
            return solve(cRow - 1, cCol, cCnt + 1, 2);
        }
        else if (map[cRow][cCol] == '+') {
            
            return solve(cRow - 1, cCol, cCnt + 1, 2);
        }
        else if (map[cRow][cCol] == '4') {
            
            return solve(cRow, cCol - 1, cCnt + 1, 3);
        }
        else if (map[cRow][cCol] == '1') {
            
            return solve(cRow, cCol + 1, cCnt + 1, 1);
        }
    }
    else if (dir == 3) {
        
        if (map[cRow][cCol] == '.') {
            
            if (cCol - 1 >= 0 && map[cRow][cCol - 1] != '.') {
                
                map[cRow][cCol] = '-';
                if (solve(cRow, cCol - 1, cCnt + 1, 3)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '-';
                    return true;
                }
                
                map[cRow][cCol] = '+';
                ++cnt;
                if (solve(cRow, cCol - 1, cCnt + 1, 3)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '+';
                    return true;
                }
                --cnt;
            }
            
            if (cRow - 1 >= 0 && map[cRow - 1][cCol] != '.') {
                
                map[cRow][cCol] = '2';
                if (solve(cRow - 1, cCol, cCnt + 1, 2)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '2';  
                    return true;
                }
            }
            
            if (cRow + 1 < R && map[cRow + 1][cCol] != '.') {
                
                map[cRow][cCol] = '1';
                if (solve(cRow + 1, cCol, cCnt + 1, 4)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '1'; 
                    return true;
                }
            }
            
            map[cRow][cCol] = '.';
            return false;
        }
        else if (map[cRow][cCol] == '-') {
            
            return solve(cRow, cCol - 1, cCnt + 1, 3);
        }
        else if (map[cRow][cCol] == '+') {
            
            return solve(cRow, cCol - 1, cCnt + 1, 3);
        }
        else if (map[cRow][cCol] == '2') {
            
            return solve(cRow - 1, cCol, cCnt + 1, 2);
        }
        else if (map[cRow][cCol] == '1') {
            
            return solve(cRow + 1, cCol, cCnt + 1, 4);
        }
    }
    else if (dir == 4) {
        
        if (map[cRow][cCol] == '.') {
            
            if (cRow + 1 < R && map[cRow + 1][cCol] != '.') {
                
                map[cRow][cCol] = '|';
                if (solve(cRow + 1, cCol, cCnt + 1, 4)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '|';
                    return true;
                }
                
                map[cRow][cCol] = '+';
                ++cnt;
                if (solve(cRow + 1, cCol, cCnt + 1, 4)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '+';
                    return true;
                }
                --cnt;
            }
            
            if (cCol - 1 >= 0 && map[cRow][cCol - 1] != '.') {
                
                map[cRow][cCol] = '3';
                if (solve(cRow, cCol - 1, cCnt + 1, 3)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '3';  
                    return true;
                }
            }
            
            if (cCol + 1 < C && map[cRow][cCol + 1] != '.') {
                
                map[cRow][cCol] = '2';
                if (solve(cRow, cCol + 1, cCnt + 1, 1)) {
                    
                    std::cout << cRow + 1 << ' ' << cCol + 1 << ' ' << '2'; 
                    return true;
                }
            }
            
            map[cRow][cCol] = '.';
            return false;
        }
        else if (map[cRow][cCol] == '|') {
            
            return solve(cRow + 1, cCol, cCnt + 1, 4);
        }
        else if (map[cRow][cCol] == '+') {
            
            return solve(cRow + 1, cCol, cCnt + 1, 4);
        }
        else if (map[cRow][cCol] == '3') {
            
            return solve(cRow, cCol - 1, cCnt + 1, 3);
        }
        else if (map[cRow][cCol] == '2') {
            
            return solve(cRow, cCol + 1, cCnt + 1, 1);
        }
    }
    
    return false;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

