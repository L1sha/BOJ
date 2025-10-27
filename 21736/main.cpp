#include <iostream>
#include <vector>
#include <queue>
#include <utility>

int main() {
    
    int N, M; std::cin >> N >> M;
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(M));
    std::vector<std::vector<char>> map(N, std::vector<char>(M));
    std::queue<std::pair<int, int>> q;
    
    for (int idx = 0; idx < N; ++idx)
        for (int idx2 = 0; idx2 < M; ++idx2) {
        
            std::cin >> map[idx][idx2];
            if (map[idx][idx2] == 'I') {
                
                q.push({idx, idx2});
                visited[idx][idx2] = true;
            }
        }
    
    int res = 0;
    
    while (!q.empty()) {
        
        const auto& [X, Y] = q.front();
        q.pop();
        
        std::vector<std::pair<int, int>> nexts{{X - 1, Y}, {X + 1, Y}, {X, Y - 1}, {X, Y + 1}};
        
        for (const auto& [x, y] : nexts) {
            
            if (x >= 0 && x < N && y >= 0 && y < M && map[x][y] != 'X' && visited[x][y] == false) {
                
                if (map[x][y] == 'P') res++;
                q.push({x, y});
                visited[x][y] = true;
            }
        }
    }
    
    if (res) std::cout << res;
    else std::cout << "TT";
    
    return 0;
}