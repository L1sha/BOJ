#include "bits/stdc++.h"

constexpr size_t N_MAX = 11, H_MAX = 20, W_MAX = 20;
const int INF = 123'456'789;

using intPair = std::pair<int, int>;

int N, H, W;

std::array<std::array<char, W_MAX>, H_MAX> map;
std::array<intPair, N_MAX> dirts;
std::array<std::array<int, N_MAX>, N_MAX> dist;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

bool get_input() {
    
    std::cin >> W >> H;
    
    if (W * H == 0) return false;
    
    N = 0;
    
    for (int row = 0; row < H; ++row) {
        
        for (int col = 0; col < W; ++col) {
            
            std::cin >> map[row][col];
            
            if (map[row][col] == '*') {
                
                dirts[++N] = {row, col};
                map[row][col] = '0' + N;
            }
            else if (map[row][col] == 'o') {
                
                dirts[0] = {row, col};
                map[row][col] = '0';
            }
        }
    }
    
    return true;
}

void getDistance() {
    
    for (int idx = 0; idx <= N; ++idx) {
        
        for (int idx2 = 0; idx2 <= N; ++idx2) {
            
            dist[idx][idx2] = INF;
        }
        dist[idx][idx] = 0;
        
        std::vector<std::vector<bool>> visited(H, std::vector<bool>(W));
        
        std::queue<std::tuple<int, int, int>> q;
        q.push({0, dirts[idx].first, dirts[idx].second});
        visited[dirts[idx].first][dirts[idx].second] = true;
        
        while (!q.empty()) {
            
            auto [cDist, cRow, cCol] = q.front();
            q.pop();
            
            std::array<intPair, 4> next{{
                
                {cRow + 1, cCol},
                {cRow - 1, cCol},
                {cRow, cCol + 1},
                {cRow, cCol - 1}
            }};
            
            for (const auto& [nRow, nCol] : next) {
                
                if (nRow < 0 || nRow >= H || nCol < 0 || nCol >= W) continue;
                
                if (visited[nRow][nCol] || map[nRow][nCol] == 'x') continue;
                
                if (map[nRow][nCol] != '.') {
                    
                    dist[idx][static_cast<size_t>(map[nRow][nCol] - '0')] = cDist + 1;
                }
                
                visited[nRow][nCol] = true;
                q.push({cDist + 1, nRow, nCol});
            }
        }
    }
}

void getMinDistSum(int bitMask, int from, int cur, int& min) {
    
    if (bitMask == 0) {
        
        min = std::min(cur, min);
        return;
    }
    
    for (int idx = 0, temp = bitMask; temp; ++idx) {
        
        if (temp & 1) {
            
            getMinDistSum(bitMask - (1 << idx), idx, cur + dist[from][idx], min);
        }
        
        temp >>= 1;
    }
}

void solve() {
    
    while (true) {
        
        if (!get_input()) return;
        
        getDistance();
        
        bool flag = false;
        
        for (int idx = 1; idx <= N; ++idx) {
            
            if (dist[0][idx] == INF) {
                
                flag = true;
                break;
            }
        }
        
        if (flag) {
            
            std::cout << -1 << '\n';
        }
        else {
            
            int min = INF;
            
            getMinDistSum((1 << (N + 1)) - 2, 0, 0, min);
            
            std::cout << min << '\n';
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    solve();
    
    return 0;
}

