#include "bits/stdc++.h"

constexpr int N_MAX = 100, NUM_MAX = 201;

struct Step {
    
    int row, col, min;
};

int N;

std::array<std::array<int, N_MAX>, N_MAX> map;
std::array<std::array<std::array<int, NUM_MAX>, N_MAX>, N_MAX> dp;
std::array<std::array<std::array<bool, NUM_MAX>, N_MAX>, N_MAX> inQ;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < N; ++col) {
            
            std::cin >> map[row][col];
            
            for (int num = 0; num < NUM_MAX; ++num) {
                
                dp[row][col][num] = 2 * NUM_MAX;
            }
        }
    }
}

void solve() {
    
    std::queue<Step> q;
    q.push({0, 0, map[0][0]});
    dp[0][0][map[0][0]] = map[0][0];
    inQ[0][0][map[0][0]] = true;
    
    while (!q.empty()) {
        
        const auto [cRow, cCol, cMin] = q.front();
        const auto cMax = dp[cRow][cCol][cMin];
        q.pop();
        inQ[cRow][cCol][cMin] = false;
        
        std::array<Step, 4> candidate {{
            
            {cRow - 1, cCol, cMin},
            {cRow + 1, cCol, cMin},
            {cRow, cCol - 1, cMin},
            {cRow, cCol + 1, cMin}
        }};
        
        for (auto& [nRow, nCol, nMin] : candidate) {
            
            if (nRow == -1 || nRow == N || nCol == -1 || nCol == N) continue;
            
            nMin = std::min(cMin, map[nRow][nCol]);
            int nMax = std::max(cMax, map[nRow][nCol]);
            
            if (nMax < dp[nRow][nCol][nMin]) {
                
                dp[nRow][nCol][nMin] = nMax;
                
                if (!inQ[nRow][nCol][nMin]) {
                    
                    q.push({nRow, nCol, nMin});
                    inQ[nRow][nCol][nMin] = true;
                }
            }
        }
    }
    
    int res = NUM_MAX;
    
    for (int num = 0; num < NUM_MAX; ++num) {
        
        res = std::min(dp[N - 1][N - 1][num] - num, res);
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

