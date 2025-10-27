#include "bits/stdc++.h"


int N, M;

std::array<std::array<int, 501>, 501> map;
std::unordered_map<int, int> memo;

int idx(int row, int col) { return row * M + col; }

int solve(int row, int col){
    
    if (idx(row, col) == N * M - 1) return 1;
    if (memo.count(idx(row, col))) return memo[idx(row, col)];
    
    int res = 0;
    
    if (row - 1 >= 0 && map[row - 1][col] < map[row][col]) res += solve(row - 1, col);
    if (row + 1 < N && map[row + 1][col] < map[row][col]) res += solve(row + 1, col);
    if (col - 1 >= 0 && map[row][col - 1] < map[row][col]) res += solve(row, col - 1);
    if (col + 1 < M && map[row][col + 1] < map[row][col]) res += solve(row, col + 1);
    
    memo[idx(row, col)] = res;
    
    return res;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < M; ++idx2) std::cin >> map[idx][idx2];
    
    std::cout << solve(0, 0);
    
    return 0;
}


