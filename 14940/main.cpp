#include "bits/stdc++.h"


int N, M;

std::array<std::array<int, 1001>, 1001> map;
std::array<std::array<int, 1001>, 1001> res;
std::array<std::array<bool, 1001>, 1001> visited;

std::queue<std::pair<std::pair<int, int>, int>> q;

void fill(int row, int col, int dist){
    
    
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::array<int, 1001> minusOne;
    std::fill(minusOne.begin(), minusOne.end(), -1);
    std::fill(res.begin(), res.end(), minusOne);
    
    std::cin >> N >> M;
    
    int targetX, targetY;
    
    for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < M; ++idx2) {
        
        std::cin >> map[idx][idx2];
        if (map[idx][idx2] == 2) { targetX = idx; targetY = idx2; }
    }
    
    q.push({{targetX, targetY}, 0});
    
    while (!q.empty()){
        
        auto temp = q.front();
        int X = temp.first.first, Y = temp.first.second, dist = temp.second;
        q.pop();
        
        if (visited[X][Y]) continue;
        
        visited[X][Y] = true;
        
        if (map[X][Y] == 0) res[X][Y] = 0;
        else {
            
            res[X][Y] = dist;
            
            if (X - 1 >= 0) q.push({{X - 1, Y}, dist + 1});
            if (X + 1 < N) q.push({{X + 1, Y}, dist + 1});
            if (Y - 1 >= 0) q.push({{X, Y - 1}, dist + 1});
            if (Y + 1 < M) q.push({{X, Y + 1}, dist + 1});
        }
    }
    
    
    for (int idx = 0; idx < N; ++idx) {
    
        for (int idx2 = 0; idx2 < M; ++idx2) {
            
            if (map[idx][idx2] == 0) std::cout << 0 << ' ';
            else std::cout << res[idx][idx2] << ' ';
        }
        std::cout << '\n';
    }
    
    
    return 0;
}


