#include "bits/stdc++.h"


int N, M;

std::array<std::array<int, 1001>, 1001> tomato;
std::array<std::array<bool, 1001>, 1001> visited;
std::queue<std::pair<std::pair<int, int>, int>> q;




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> M >> N;
    
    for (int rIdx = 0; rIdx < N; ++rIdx) for (int cIdx = 0; cIdx < M; ++cIdx){
        
        std::cin >> tomato[rIdx][cIdx];
        if (tomato[rIdx][cIdx] == 1) q.push({{rIdx, cIdx}, 0});
    }
    
    int res = 0;
    
    while (!q.empty()){
        
        auto temp = q.front();
        q.pop();
        
        int X = temp.first.first, Y = temp.first.second, day = temp.second;
        
        if (visited[X][Y]) continue;
        visited[X][Y] = true;
        res = day;
        
        if (X - 1 >= 0 && !visited[X - 1][Y] && tomato[X - 1][Y] == 0) q.push({{X - 1, Y}, day + 1});
        if (X + 1 < N && !visited[X + 1][Y] && tomato[X + 1][Y] == 0) q.push({{X + 1, Y}, day + 1});
        if (Y - 1 >= 0 && !visited[X][Y - 1] && tomato[X][Y - 1] == 0) q.push({{X, Y - 1}, day + 1});
        if (Y + 1 < M && !visited[X][Y + 1] && tomato[X][Y + 1] == 0) q.push({{X, Y + 1}, day + 1});
    }
    
    for (int rIdx = 0; rIdx < N; ++rIdx) for (int cIdx = 0; cIdx < M; ++cIdx) if (!visited[rIdx][cIdx] && tomato[rIdx][cIdx] == 0){
        
        std::cout << -1;
        return 0;
    }
    
    std::cout << res;
    
    return 0;
}


