#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M, adjBlanksCnt;
std::array<std::array<char, 1000>, 1000> map;
std::array<std::array<int, 1000>, 1000> res;
std::array<std::array<bool, 1000>, 1000> visited;
std::unordered_map<int, int> howManyAdjBlanks;

void solve(int row, int col) {
    
    std::vector<intPair> adjBlanks;
    std::queue<intPair> q;
    q.push({row, col});
    int cnt = 0, topRow, topCol;
    
    while (!q.empty()) {
        
        topRow = q.front().first;
        topCol = q.front().second;
        q.pop();
        
        if (visited[topRow][topCol]) continue;
        visited[topRow][topCol] = true;
        cnt++;
        adjBlanks.push_back({topRow, topCol});
        
        if (topRow - 1 >= 0 && !visited[topRow - 1][topCol]) q.push({topRow - 1, topCol});
        if (topRow + 1 < N && !visited[topRow + 1][topCol]) q.push({topRow + 1, topCol});
        if (topCol - 1 >= 0 && !visited[topRow][topCol - 1]) q.push({topRow, topCol - 1});
        if (topCol + 1 < M && !visited[topRow][topCol + 1]) q.push({topRow, topCol + 1});
    }

    for (auto& el : adjBlanks) res[el.first][el.second] = adjBlanksCnt;
    howManyAdjBlanks[adjBlanksCnt++] = cnt;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) {
        
        std::cin >> map[row][col];
        if (map[row][col] == '1') {
            
            visited[row][col] = true;
        }
    }
    
    for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) if (map[row][col] == '0' && !visited[row][col]) solve(row, col);
    
    for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) if (map[row][col] == '1') {
        
        std::set<int> s;
        
        res[row][col] = 1;
        if (row - 1 >= 0 && map[row - 1][col] == '0') s.insert(res[row - 1][col]);
        if (row + 1 < N && map[row + 1][col] == '0') s.insert(res[row + 1][col]);
        if (col - 1 >= 0 && map[row][col - 1] == '0') s.insert(res[row][col - 1]);
        if (col + 1 < M && map[row][col + 1] == '0') s.insert(res[row][col + 1]);
        
        for (auto& el : s) res[row][col] += howManyAdjBlanks[el];
    }
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
        
            if (map[row][col] == '0') std::cout << 0;
            else std::cout << res[row][col] % 10;
        }
        
        std::cout << '\n';
    }
    
    return 0;
}

