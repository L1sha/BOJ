#include "bits/stdc++.h"


int R, C, M;
int res;

struct shark{
    
    int speed = 0, dir = 1, size = 0, lastmove = 0;
    
    shark() = default;
    shark(int s, int d, int sz) : speed(s), dir(d), size(sz) {} 
    
    bool operator< (const shark& rhs) {
        
        return size < rhs.size;
    }
};

std::array<std::array<std::vector<shark>, 101>, 101> map;

bool isShark(int row, int col) {
    
    return !map[row][col].empty();
}

void killShark(int col) { 
    
    int sz;
    for (int row = 1; row <= R; ++row) if (isShark(row, col)) {
        
        res += map[row][col][0].size;
        map[row][col].clear();
        break;
    }   
}

void moveShark(int row, int col, int idx, int t) {
    
    shark temp = map[row][col][idx];
    map[row][col].erase(map[row][col].begin() + idx);
    
    int remaining = temp.speed, togo, dir = temp.dir, resRow = row, resCol = col;
    
    while (remaining) {
        
        switch (dir) {
            
            case 1:
            
            if (remaining > resRow - 1) {
                
                togo = resRow - 1;
                dir = 2;
            }
            else togo = remaining;
            
            remaining -= togo;
            resRow -= togo;
            
            break;
            
            case 2:
            
            if (remaining > R - resRow) {
                
                togo = R - resRow;
                dir = 1;
            }
            else togo = remaining;
            
            remaining -= togo;
            resRow += togo;
            
            break;
            
            case 3:
            
            if (remaining > C - resCol) {
                
                togo = C - resCol;
                dir = 4;
            }
            else togo = remaining;
            
            remaining -= togo;
            resCol += togo;
            
            break;
            
            case 4:
            
            if (remaining > resCol - 1) {
                
                togo = resCol - 1;
                dir = 3;
            }
            else togo = remaining;
            
            remaining -= togo;
            resCol -= togo;
            
            break;
        }
    }
    
    temp.dir = dir;
    temp.lastmove = t;
    
    map[resRow][resCol].push_back(temp);
}

void sharkFight() {
    
    for (int row = 1; row <= R; ++row) for (int col = 1; col <= C; ++col) if (isShark(row, col)) {
        
        shark temp = *max_element(map[row][col].begin(), map[row][col].end());
        map[row][col].clear();
        map[row][col].push_back(temp);
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> R >> C >> M;
    int r,c,s,d,z;
    
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> r >> c >> s >> d >> z;
        map[r][c].push_back(shark(s, d, z));
    }
    
    for (int t = 1; t <= C; ++t) {
        
        killShark(t);
        
        for (int row = 1; row <= R; ++row) for (int col = 1; col <= C; ++col) if (isShark(row, col)) {
            
            for (int idx = 0; idx < map[row][col].size(); ++idx){
                
                if (map[row][col][idx].lastmove != t) {
                
                    moveShark(row, col, idx, t);
                    idx--;
                }
            }
        }
        
        sharkFight();
        
        /*
        std::cout << "Res : " << res << '\n';
        for (int row = 1; row <= R; ++row) {
            
            for (int col = 1; col <= C; ++col) {
                
                if (isShark(row, col)) std::cout << map[row][col][0].size << ' ';
                else std::cout << "0 ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
        */
    }
    
    std::cout << res;
    
    return 0;
}

