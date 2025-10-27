#include "bits/stdc++.h"

constexpr int H_MAX = 100, W_MAX = 100, INF = 1e8;

int T, H, W;
std::array<std::pair<int, int>, 2> prisoner;

struct Point {
    
    int row, col, depth, dist;
    
    bool operator< (const Point& rhs) const {
        
        return dist < rhs.dist;
    }
    
    bool operator> (const Point& rhs) const {
        
        return dist > rhs.dist;
    }
};

std::array<std::array<char, W_MAX>, H_MAX> map;
std::array<std::array<std::array<std::vector<Point>, 2>, W_MAX>, H_MAX> adjL;
std::array<std::array<std::array<std::array<bool, 3>, 2>, W_MAX>, H_MAX> visited;
std::array<std::array<std::array<std::array<int, 3>, 2>, W_MAX>, H_MAX> dist;
std::priority_queue<Point, std::vector<Point>, std::greater<>> pq;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> H >> W;
    for (int row = 0, cnt = 0; row < H; ++row) {
        
        for (int col = 0; col < W; ++col) {
            
            std::cin >> map[row][col];
            
            if (map[row][col] == '$') {
                
                prisoner[cnt++] = {row, col};
                map[row][col] = '.';
            }
            
            for (int depth = 0; depth < 2; ++depth) {
                
                adjL[row][col][depth].clear();
                
                for (int distType = 0; distType < 3; ++distType) {
                    
                    dist[row][col][depth][distType] = INF;
                    visited[row][col][depth][distType] = false;
                }
            }
        }
    }
}

void make_adjL() {
    
    for (int row = 0; row < H; ++row) {
        
        for (int col = 0; col < W; ++col) {
            
            if (map[row][col] == '*') continue;
            
            int depth = 0;
            
            if (map[row][col] == '#') {
                
                adjL[row][col][0].push_back({row, col, 1, 1});
                depth = 1;
            }
            
            if (row + 1 < H) {
                
                if (map[row + 1][col] == '.') {
                    
                    adjL[row][col][depth].push_back({row + 1, col, 0, 0});
                    adjL[row + 1][col][0].push_back({row, col, 0, 0});
                }
                else if (map[row + 1][col] == '#') {
                    
                    adjL[row][col][depth].push_back({row + 1, col, 0, 0});
                    adjL[row + 1][col][1].push_back({row, col, 0, 0});
                }
            }
            
            if (col + 1 < W) {
                
                if (map[row][col + 1] == '.') {
                    
                    adjL[row][col][depth].push_back({row, col + 1, 0, 0});
                    adjL[row][col + 1][0].push_back({row, col, 0, 0});
                }
                else if (map[row][col + 1] == '#') {
                    
                    adjL[row][col][depth].push_back({row, col + 1, 0, 0});
                    adjL[row][col + 1][1].push_back({row, col, 0, 0});
                }
            }
        }
    }
}

void dijkstra(int distType) {
    
    while (!pq.empty()) {
        
        auto [cRow, cCol, cDepth, cDist] = pq.top();
        pq.pop();
        
        if (visited[cRow][cCol][cDepth][distType]) continue;
        visited[cRow][cCol][cDepth][distType] = true;
        dist[cRow][cCol][cDepth][distType] = cDist;
        
        for (const auto& [nRow, nCol, nDepth, nDist] : adjL[cRow][cCol][cDepth]) {
            
            if (!visited[nRow][nCol][nDepth][distType]) {
                
                pq.push({nRow, nCol, nDepth, cDist + nDist});
            }
        }
    }
}

void solve() {
    
    make_adjL();
    
    for (int row = 0; row < H; ++row) {
        
        if (map[row][0] != '*') pq.push({row, 0, 0, 0});
        
        if (map[row][W - 1] != '*') pq.push({row, W - 1, 0, 0});
    }
    for (int col = 1; col < W - 1; ++col) {
        
        if (map[0][col] != '*') pq.push({0, col, 0, 0});
        
        if (map[H - 1][col] != '*') pq.push({H - 1, col, 0, 0});
    }
    dijkstra(0);
    
    auto [pX1, pY1] = prisoner[0];
    pq.push({pX1, pY1, 0, 0});
    dijkstra(1);
    
    auto [pX2, pY2] = prisoner[1];
    pq.push({pX2, pY2, 0, 0});
    dijkstra(2);
    
    int res = dist[pX1][pY1][0][0] + dist[pX2][pY2][0][0];
    
    for (int row = 0, cand; row < H; ++row) {
        
        for (int col = 0; col < W; ++col) {
            
            cand = dist[row][col][0][0] + dist[row][col][0][1] + dist[row][col][0][2];
            if (map[row][col] == '#') ++cand;
            
            res = std::min(res, cand);
        }
    }
    
    std::cout << res << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    std::cin >> T;
    while (T--) {
        
        get_input();
        solve();
    }
    
    return 0;
}