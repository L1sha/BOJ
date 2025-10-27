#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M;
const int limit = 10;
const int left = 0, right = 1, up = 2, down = 3;
const int bothCannotMove = 0, bothCanMove = 10, redCanMove = 11, blueCanMove = 12;

const std::array<int, 4> dirs = {left, right, up, down};
bool isRedIn, isBlueIn;

std::array<std::array<int, 10>, 10> wall;
intPair red, blue, hole;



void move(intPair& marble, int dir){
    
    switch(dir) {
        
        case left:
        marble.second--;
        break;
        
        case right:
        marble.second++;
        break;
        
        case up:
        marble.first--;
        break;
        
        case down:
        marble.first++;
        break;
    }
}

int moveAvailable(int dir){
    
    if (blue == hole) return bothCannotMove;    // no need to move
    else if (red == hole) {
        
        switch(dir) {
            
            case left:
            if (wall[blue.first][blue.second - 1]) return bothCannotMove;
            else return blueCanMove;
            break;
            
            case right:
            if (wall[blue.first][blue.second + 1]) return bothCannotMove;
            else return blueCanMove;
            break;
            
            case up:
            if (wall[blue.first - 1][blue.second]) return bothCannotMove;
            else return blueCanMove;
            break;
            
            case down:
            if (wall[blue.first + 1][blue.second]) return bothCannotMove;
            else return blueCanMove;
            break;
        }
    }
    else switch(dir) {
            
        case left:
        if (wall[red.first][red.second - 1]){
            
            if (wall[blue.first][blue.second - 1]) return bothCannotMove;
            else if (red.first == blue.first && red.second == blue.second - 1) return bothCannotMove;
            else return blueCanMove;
        }
        else {
            
            if (wall[blue.first][blue.second - 1]) {
                
                if (red.first == blue.first && red.second - 1 == blue.second) return bothCannotMove;
                else return redCanMove;
            }
            else return bothCanMove;
        }
        break;
        
        case right:
        if (wall[red.first][red.second + 1]){
            
            if (wall[blue.first][blue.second + 1]) return bothCannotMove;
            else if (red.first == blue.first && red.second == blue.second + 1) return bothCannotMove;
            else return blueCanMove;
        }
        else {
            
            if (wall[blue.first][blue.second + 1]) {
                
                if (red.first == blue.first && red.second + 1 == blue.second) return bothCannotMove;
                else return redCanMove;
            }
            else return bothCanMove;
        }
        break;
        
        case up:
        if (wall[red.first - 1][red.second]){
            
            if (wall[blue.first - 1][blue.second]) return bothCannotMove;
            else if (red.first == blue.first - 1 && red.second == blue.second) return bothCannotMove;
            else return blueCanMove;
        }
        else {
            
            if (wall[blue.first - 1][blue.second]) {
                
                if (red.first - 1 == blue.first && red.second == blue.second) return bothCannotMove;
                else return redCanMove;
            }
            else return bothCanMove;
        }
        break;
        
        case down:
        if (wall[red.first + 1][red.second]){
            
            if (wall[blue.first + 1][blue.second]) return bothCannotMove;
            else if (red.first == blue.first + 1 && red.second == blue.second) return bothCannotMove;
            else return blueCanMove;
        }
        else {
            
            if (wall[blue.first + 1][blue.second]) {
                
                if (red.first + 1 == blue.first && red.second == blue.second) return bothCannotMove;
                else return redCanMove;
            }
            else return bothCanMove;
        }
        break;
    }
}

int play(int remaining){
    
    if (remaining == 0) return -1;
    
    std::array<int, 4> res;
    intPair redSave = red, blueSave = blue;
    int canMove;
    
    for (auto& dir : dirs){
        
        while (canMove = moveAvailable(dir)){
            
            switch(canMove) {
                
                case bothCanMove:
                move(blue, dir);
                move(red, dir);
                break;
                
                case redCanMove:
                move(red, dir);
                break;
                
                case blueCanMove:
                move(blue, dir);
                break;
            };
        }
            
        if (blue == hole) res[dir] = -1;
        else if (red == hole) return (limit - remaining + 1);
        else res[dir] = play(remaining - 1);
        
        red = redSave;
        blue = blueSave;
    }
    
    if (std::accumulate(res.begin(), res.end(), 0) == -4) return -1;
    
    int min = limit + 1;
    for (auto& el : res) if (el != -1) min = std::min(min, el);
    
    return min;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    char temp;
    
    for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col){
        
        std::cin >> temp;
        if (temp == '#') wall[row][col] = true;
        else if (temp == 'B') blue = {row, col};
        else if (temp == 'R') red = {row, col};
        else if (temp == 'O') hole = {row, col};
    }
    
    int res = play(limit);
    
    std::cout << res;
    
    return 0;
}


