#include "bits/stdc++.h"


constexpr int N_MAX = 1001;

int N, M;

std::array<std::array<int, N_MAX>, N_MAX> map, partialSum, memo;

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int row = 1; row <= N; ++row) {
        
        for (int col = 1; col <= M; ++col) {
            
            std::cin >> map[row][col];
            partialSum[row][col] = partialSum[row][col - 1] + map[row][col];
        }
    }
    
    for (int col = 1; col <= M; ++col) {
        
        memo[N][col] = partialSum[N][M] - partialSum[N][col - 1];
    }
    
    for (int row = N - 1; row >= 1; --row) {
        
        std::priority_queue<int> left;
        std::priority_queue<std::pair<int, int>> right;
        int leftMax, rightMax;
        
        for (int col = 1; col <= M; ++col) {
            
            right.push({memo[row + 1][col] + partialSum[row][col], col});
        }
        
        memo[row][1] = right.top().first;
        
        for (int col = 2; col <= M; ++col) {
            
            left.push(memo[row + 1][col - 1] - partialSum[row][col - 2]);
            
            leftMax = left.top() + partialSum[row][col];
            
            while (right.top().second < col) {
                
                right.pop();
            }
            
            rightMax = right.top().first - partialSum[row][col - 1];
            
            memo[row][col] = std::max(leftMax, rightMax);
        }
    }
    
    std::cout << memo[1][1];
    
    return 0;
}

