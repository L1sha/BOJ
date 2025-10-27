#include "bits/stdc++.h"


int N, M;

std::array<std::array<int, 101>, 101> minDist;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    std::array<int, 101> temp;
    std::fill(temp.begin(), temp.begin() + N + 1, 1e9);
    std::fill(minDist.begin(), minDist.begin() + N + 1, temp);
    
    int from, to, cost;
    
    while (M--){
        
        std::cin >> from >> to >> cost;
        if (cost < minDist[from][to]) minDist[from][to] = cost;
    }
    
    for (int idx = 1; idx <= N; ++idx) minDist[idx][idx] = 0;
    
    for (int mid = 1; mid <= N; ++mid) for (int start = 1; start <= N; ++start) for (int end = 1; end <= N; ++end){
        
        minDist[start][end] = std::min(minDist[start][end], minDist[start][mid] + minDist[mid][end]);
    }
    
    for (int start = 1; start <= N; ++start) {
    
        for (int end = 1; end <= N; ++end) {
        
            if (minDist[start][end] == 1e9) std::cout << 0 << ' ';
            else std::cout << minDist[start][end] << ' ';
        }
        
        std::cout << '\n';
    }
    
    return 0;
}



