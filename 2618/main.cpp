#include "bits/stdc++.h"


using intPair = std::pair<int, int>;    // <row, col>
using resPair = std::pair<int, bool>;   // <dist sum, consecutive move>

int N, W;

std::vector<intPair> cases;                             // cases[0] = (N, N), cases[1] = (1, 1), cases[2...] = real cases
std::vector<std::vector<std::optional<resPair>>> memo;  // [step][idx of second point] <- first point must be on cases[step + 1]

int dist (int idx1, int idx2) {
    
    return std::abs(cases[idx1].first - cases[idx2].first) + std::abs(cases[idx1].second - cases[idx2].second);
}

resPair solve(int step, int idx) {
    
    if (step == W) return {0, true};
    if (memo[step][idx].has_value()) return memo[step][idx].value();
    
    int consecutive = dist(step + 1, step + 2) + (solve(step + 1, idx)).first;
    int nonConsecutive = dist(idx, step + 2) + (solve(step + 1, step + 1)).first;
    
    if (consecutive <= nonConsecutive) memo[step][idx] = {consecutive, true};
    else memo[step][idx] = {nonConsecutive, false};
    
    return memo[step][idx].value();
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> W;
    
    memo.resize(W);
    for (int idx = 0; idx < W; ++idx) memo[idx].resize(1 + idx);
    
    cases.resize(W + 2);
    cases[1] = {1, 1};
    cases[0] = {N, N};
    for (int idx = 2; idx < W + 2; ++idx) std::cin >> cases[idx].first >> cases[idx].second;
    
    
    std::cout << (solve(0, 0)).first << '\n';
    
    int car = 1, secondPoint = 0;
    resPair temp;
    
    for (int step = 0; step < W; ++step) {
        
        temp = memo[step][secondPoint].value();
        if (!temp.second) {
            
            car = (car % 2) + 1;
            secondPoint = step + 1;
        }
        
        std::cout << car << '\n';
    }
    
    return 0;
}

