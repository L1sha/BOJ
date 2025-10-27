#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M;

std::array<std::array<int, 8>, 8> map;
std::array<std::array<int, 8>, 8> newMap;
std::vector<intPair> initialSafe;



int solve() {
    
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(M, false));
    
    for (int row = 0; row < N; ++row)
        for (int col = 0; col < M; ++col) 
            if (!visited[row][col] && newMap[row][col] == 2) {
                
                std::queue<intPair> q;
                q.push({row, col});
                
                intPair front;
                
                while (!q.empty()) {
                    
                    front = q.front();
                    q.pop();
                    
                    if (visited[front.first][front.second]) continue;
                    visited[front.first][front.second] = true;
                    
                    newMap[front.first][front.second] = 2;
                    
                    if (front.first - 1 >= 0 && !visited[front.first - 1][front.second] && newMap[front.first - 1][front.second] != 1) q.push({front.first - 1, front.second});
                    if (front.first + 1 < N && !visited[front.first + 1][front.second] && newMap[front.first + 1][front.second] != 1) q.push({front.first + 1, front.second});
                    if (front.second - 1 >= 0 && !visited[front.first][front.second - 1] && newMap[front.first][front.second - 1] != 1) q.push({front.first, front.second - 1});
                    if (front.second + 1 < M && !visited[front.first][front.second + 1] && newMap[front.first][front.second + 1] != 1) q.push({front.first, front.second + 1});
                }
            }
            
    int cnt = 0;
    
    for (int row = 0; row < N; ++row)
        for (int col = 0; col < M; ++col) 
            if (newMap[row][col] == 0) 
                cnt++;
    
    return cnt;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) {
        
        std::cin >> map[row][col];
        if (!map[row][col]) initialSafe.push_back({row, col});
    }
    
    int res = 0, temp;
    
    for (auto it = initialSafe.begin(); it != initialSafe.end(); ++it)
        for (auto it2 = it + 1; it2 != initialSafe.end(); ++it2)
            for (auto it3 = it2 + 1; it3 != initialSafe.end(); ++it3) {
                
                newMap = map;
                newMap[(*it).first][(*it).second] = 1;
                newMap[(*it2).first][(*it2).second] = 1;
                newMap[(*it3).first][(*it3).second] = 1;
                
                temp = solve();
                res = std::max(res, temp);
            }
    
    std::cout << res;
    
    return 0;
}


