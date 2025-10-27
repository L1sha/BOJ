#include "bits/stdc++.h"

using intPair = std::pair<int, int>;

int T, N, M, W;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--){
        
        std::cin >> N >> M >> W;
        
        std::vector<std::vector<int>> adjM(N + 1, std::vector<int>(N + 1, 1e9));
        for (int idx = 1; idx <= N; ++idx) adjM[idx][idx] = 0;
        
        int from, to, weight;
        
        while (M--){
            
            std::cin >> from >> to >> weight;
            adjM[from][to] = std::min(adjM[from][to], weight);
            adjM[to][from] = std::min(adjM[to][from], weight);
        }
        
        while (W--){
            
            std::cin >> from >> to >> weight;
            adjM[from][to] = std::min(adjM[from][to], -weight);
        }
        
        for (int mid = 1; mid <= N; ++mid) for (int start = 1; start <= N; ++start) for (int end = 1; end <= N; ++end){
            
            adjM[start][end] = std::min(adjM[start][end], adjM[start][mid] + adjM[mid][end]);
        }
        
        std::string s = "NO";
        
        for (int start = 1; start <= N; ++start) {
            
            for (int end = 1; end <= N; ++end){
            
                if (adjM[start][end] + adjM[end][start] < 0){
                    
                    s = "YES";
                    break;
                }
            }
            
            if (s == "YES") break;
        }
        
        std::cout << s << '\n';
    }
    
    
    return 0;
}


