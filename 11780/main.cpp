#include "bits/stdc++.h"


int N, M, from, to, weight;

std::array<std::array<int, 101>, 101> res;
std::array<std::array<int, 101>, 101> layover;
std::array<std::array<std::optional<std::pair<int, std::string>>, 101>, 101> memo;

std::pair<int, std::string> route(const int& start, const int& end) {
    
    if (memo[start][end].has_value()) return memo[start][end].value();
    
    if (layover[start][end] == start) {
        
        memo[start][end] = {1, std::to_string(start) + " "};
        return memo[start][end].value();
    }
    
    auto left = route(start, layover[start][end]);
    auto right = route(layover[start][end], end);
    memo[start][end] = {left.first + right.first, left.second + right.second};
    return memo[start][end].value();
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) for (int idx2 = idx + 1; idx2 <= N; ++idx2) {
        
        res[idx][idx2] = 1e9;
        res[idx2][idx] = 1e9;
    }
    
    while (M--) {
        
        std::cin >> from >> to >> weight;
        
        if (res[from][to] > weight) {
         
            res[from][to] = weight;
            layover[from][to] = from;
        }
    }
    
    for (int mid = 1; mid <= N; ++mid) for (int start = 1; start <= N; ++start) for (int end = 1; end <= N; ++end) {
        
        if (res[start][end] > res[start][mid] + res[mid][end]) {
            
            res[start][end] = res[start][mid] + res[mid][end];
            layover[start][end] = mid;
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        for (int idx2 = 1; idx2 <= N; ++idx2) {
            
            if (res[idx][idx2] == 1e9) res[idx][idx2] = 0;
            std::cout << res[idx][idx2] << ' ';
        }
        
        std::cout << '\n';
    }
    
    for (int idx = 1; idx <= N; ++idx) for (int idx2 = 1; idx2 <= N; ++idx2) {
        
        if (res[idx][idx2] == 0) std::cout << "0\n";
        else {
            
            auto [cnt, output] = route(idx, idx2);
            std::cout << cnt + 1 << ' ' << output << idx2 << '\n';
        }
    }
    
    return 0;
}

