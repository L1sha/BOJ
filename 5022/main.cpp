#include "bits/stdc++.h"

constexpr int N_MAX = 101, IMPOSSIBLE = 1e9;

int N, M;

std::array<std::pair<int, int>, 2> A, B;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    std::cin >> A[0].first >> A[0].second >> A[1].first >> A[1].second;
    std::cin >> B[0].first >> B[0].second >> B[1].first >> B[1].second;
}

std::array<std::pair<int, int>, 4> move{{
    
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
}};

int BFS(const std::array<std::pair<int, int>, 2>& A, const std::array<std::pair<int, int>, 2>& B) {
    
    int res = 0;
    
    std::queue<std::pair<std::pair<int, int>, int>> q;
    std::vector<std::vector<std::pair<int, int>>> parent(N + 1, 
        std::vector<std::pair<int, int>>(M + 1));
    std::vector<std::vector<bool>> visited(N + 1, 
        std::vector<bool>(M + 1));
    
    q.push({A[0], 0});
    visited[A[0].first][A[0].second] = true;
    visited[B[0].first][B[0].second] = true;
    visited[B[1].first][B[1].second] = true;
    
    while (!q.empty()) {
        
        bool flag = false;
        
        auto [loc, dist] = q.front();
        auto [cX, cY] = loc;
        q.pop();
        
        for (const auto& [dX, dY] : move) {
            
            auto nX = cX + dX, nY = cY + dY;
            
            if (nX < 0 || nX > N || nY < 0 || nY > M) continue;
            if (visited[nX][nY]) continue;
            
            parent[nX][nY] = {cX, cY};
            
            if (A[1] == std::make_pair(nX, nY)) {
                
                res = dist + 1;
                flag = true;
                break;
            }
            
            visited[nX][nY] = true;
            q.push({{nX, nY}, dist + 1});
        }
        
        if (flag) {
            
            while (!q.empty()) q.pop();
        }
    }
    
    std::fill(visited.begin(), visited.end(), std::vector<bool>(M + 1));
    
    visited[A[1].first][A[1].second] = true;
    
    for (auto cursor = A[1]; cursor != A[0]; ) {
        
        cursor = parent[cursor.first][cursor.second];
        visited[cursor.first][cursor.second] = true;
    }
    
    q.push({B[0], 0});
    visited[B[0].first][B[0].second] = true;
    
    while (!q.empty()) {
        
        auto [loc, dist] = q.front();
        auto [cX, cY] = loc;
        q.pop();
        
        for (const auto& [dX, dY] : move) {
            
            auto nX = cX + dX, nY = cY + dY;
            
            if (nX < 0 || nX > N || nY < 0 || nY > M) continue;
            if (visited[nX][nY]) continue;
            
            if (B[1] == std::make_pair(nX, nY)) return res + dist + 1;
            
            visited[nX][nY] = true;
            q.push({{nX, nY}, dist + 1});
        }
    }
    
    return IMPOSSIBLE;
}

void solve() {
    
    int res = IMPOSSIBLE;
    
    res = std::min(res, BFS(A, B));
    res = std::min(res, BFS(B, A));
    
    if (res == IMPOSSIBLE) std::cout << "IMPOSSIBLE";
    else std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

