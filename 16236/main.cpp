#include "bits/stdc++.h"


using intPair = std::pair<int, int>;    // <row, col>
using destination = std::pair<int, intPair>;    // <dist, pos>

int N;

std::array<std::array<int, 20>, 20> map;

intPair pos;
int size = 2, cnt = 0;

destination solve() {
    
    std::queue<destination> q;
    q.push({0, pos});
    
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));
    std::vector<destination> candidates;
    destination front;
    int dist, row, col;
    
    while (!q.empty()) {
        
        front = q.front();
        q.pop();
        
        dist = front.first;
        row = front.second.first;
        col = front.second.second;
        
        if (!candidates.empty() && candidates[0].first < dist) break;
        
        if (visited[row][col]) continue;
        visited[row][col] = true;
        
        if (map[row][col] && map[row][col] < size) candidates.push_back(front);
        
        if (row - 1 >= 0 && !visited[row - 1][col] && map[row - 1][col] <= size) q.push({dist + 1, {row - 1, col}});
        if (row + 1 < N && !visited[row + 1][col] && map[row + 1][col] <= size) q.push({dist + 1, {row + 1, col}});
        if (col - 1 >= 0 && !visited[row][col - 1] && map[row][col - 1] <= size) q.push({dist + 1, {row, col - 1}});
        if (col + 1 < N && !visited[row][col + 1] && map[row][col + 1] <= size) q.push({dist + 1, {row, col + 1}});
    }
    
    if (candidates.empty()) return {0, pos};
    else return *std::min_element(candidates.begin(), candidates.end());
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int row = 0; row < N; ++row) for (int col = 0; col < N; ++col) {
        
        std::cin >> map[row][col];
        if (map[row][col] == 9) {
            
            map[row][col] = 0;
            pos = {row, col};
        }
    }
    
    int t = 0;
    destination res;
    
    while (true) {
        
        res = solve();
        
        if (!res.first) break;
        t += res.first;
        pos = res.second;
        map[pos.first][pos.second] = 0;
        
        if (++cnt == size) {
            
            size++;
            cnt = 0;
        }
    }
    
    std::cout << t;
    
    return 0;
}


