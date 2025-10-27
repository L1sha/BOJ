#include "bits/stdc++.h"


int T, N, M, K;


void solve(int rIdx, int cIdx, std::vector<std::vector<bool>>& map){
    
    map[rIdx][cIdx] = false;
    if (rIdx - 1 >= 0 && map[rIdx - 1][cIdx]) solve(rIdx - 1, cIdx, map);
    if (rIdx + 1 < N && map[rIdx + 1][cIdx]) solve(rIdx + 1, cIdx, map);
    if (cIdx - 1 >= 0 && map[rIdx][cIdx - 1]) solve(rIdx, cIdx - 1, map);
    if (cIdx + 1 < M && map[rIdx][cIdx + 1]) solve(rIdx, cIdx + 1, map);
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> N >> M >> K;
        
        std::vector<std::vector<bool>> map(N, std::vector<bool>(M, false));
        
        int x, y;
        while (K--) { std::cin >> x >> y; map[x][y] = true; }
        
        int res = 0;
        
        for (int rIdx = 0; rIdx < N; ++rIdx) for (int cIdx = 0; cIdx < M; ++cIdx) if (map[rIdx][cIdx]){
            
            solve(rIdx, cIdx, map);
            
            res++;
        }
        
        std::cout << res << '\n';
    }
    
    return 0;
}


