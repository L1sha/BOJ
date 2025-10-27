#include "bits/stdc++.h"

using info = std::tuple<int, int, int, int>;
// <X, Y, canBreak, distFrom(1,1)>

int N, M;

std::array<std::array<char, 1001>, 1001> map;
std::array<std::array<std::array<bool, 2>, 1001>, 1001> visited;

std::queue<info> q;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    char temp;
    for (int idx = 1; idx <= N; ++idx) for (int idx2 = 1; idx2 <= M; ++idx2) std::cin >> map[idx][idx2];
    
    q.push({1, 1, 1, 1});
    
    info front;
    int res = -1;
    int X, Y, canBreak, dist;
    
    while (!q.empty()) {
        
        front = q.front();
        q.pop();
        
        X = std::get<0>(front);
        Y = std::get<1>(front);
        canBreak = std::get<2>(front);
        dist = std::get<3>(front);
        
        if (visited[X][Y][canBreak]) continue;
        visited[X][Y][canBreak] = true;
        
        if (X == N && Y == M) {
            
            res = dist;
            break;
        }
        
        if (X - 1 >= 1) {
            
            if (map[X - 1][Y] == '1') {
                
                if (canBreak && !visited[X - 1][Y][0]) q.push({X - 1, Y, 0, dist + 1});
            }
            else {
                
                if (!visited[X - 1][Y][canBreak]) q.push({X - 1, Y, canBreak, dist + 1});
            }
        }
        
        if (X + 1 <= N) {
            
            if (map[X + 1][Y] == '1') {
                
                if (canBreak && !visited[X + 1][Y][0]) q.push({X + 1, Y, 0, dist + 1});
            }
            else {
                
                if (!visited[X + 1][Y][canBreak]) q.push({X + 1, Y, canBreak, dist + 1});
            }
        }
        
        if (Y - 1 >= 1) {
            
            if (map[X][Y - 1] == '1') {
                
                if (canBreak && !visited[X][Y - 1][0]) q.push({X, Y - 1, 0, dist + 1});
            }
            else {
                
                if (!visited[X][Y - 1][canBreak]) q.push({X, Y - 1, canBreak, dist + 1});
            }
        }
        
        if (Y + 1 <= M) {
            
            if (map[X][Y + 1] == '1') {
                
                if (canBreak && !visited[X][Y + 1][0]) q.push({X, Y + 1, 0, dist + 1});
            }
            else {
                
                if (!visited[X][Y + 1][canBreak]) q.push({X, Y + 1, canBreak, dist + 1});
            }
        }
    }
    
    std::cout << res;
    
    return 0;
}


