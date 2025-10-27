#include "bits/stdc++.h"

const std::array<std::pair<int, int>, 8> nextMoves = {{{2, 1}, {1, 2}, {-2, 1}, {-1, 2}, {-2, -1}, {-1, -2}, {2, -1}, {1, -2}}};

int N, sX, sY, eX, eY;

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> sX >> sY >> eX >> eY;
}

void solve() {
    
    int T;
    std::cin >> T;
    
    while (T--) {
        
        get_input();
        
        if (sX == eX && sY == eY) {
            
            std::cout << 0 << '\n';
            continue;
        }
        
        std::vector<std::vector<int>> visited(N, std::vector<int>(N, 0));
        
        std::queue<std::pair<int, int>> q;
        q.push({sX, sY});
        visited[sX][sY] = 1;
        
        bool isDone = false;
        
        while (!q.empty()) {
            
            auto [cX, cY] = q.front();
            q.pop();
            
            for (auto [nX, nY] : nextMoves) {
                
                if (cX + nX >= 0 && cX + nX < N && cY + nY >= 0 && cY + nY < N) {
                    
                    if (cX + nX == eX && cY + nY == eY) {
                        
                        isDone = true;
                        std::cout << visited[cX][cY] << '\n';
                        break;
                    }
                    
                    if (visited[cX + nX][cY + nY]) continue;
                    
                    visited[cX + nX][cY + nY] = visited[cX][cY] + 1;
                    q.push({cX + nX, cY + nY});
                }
            }
            
            if (isDone) break;
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    solve();
    
    return 0;
}