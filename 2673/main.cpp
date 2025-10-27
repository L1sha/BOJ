#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N;

std::array<std::array<std::optional<int>, 200>, 200> memo;
std::array<intPair, 100> lines;



void get_input() {
    
    std::cin >> N;
    
    for (int idx = 0, input1, input2; idx < N; ++idx) {
        
        std::cin >> input1 >> input2;
        input1--;
        input2--;
        lines[idx * 2] = {std::min(input1, input2), std::max(input1, input2)};
        lines[idx * 2 + 1] = {std::max(input1, input2), 100 + std::min(input1, input2)};
    }
    
    N *= 2;
    
    for (int idx = 0; idx < N; ++idx) {
        
        firstSet[idx] = lines[idx].first;
        secondSet[idx] = lines[idx].second;
    }
    
    std::sort(lines.begin(), lines.begin() + N);
    std::sort(firstSet.begin(), firstSet.begin() + N);
    std::sort(secondSet.begin(), secondSet.begin() + N);
}

int subSolve(int l, int r, const int& idx) {
    
    if (memo[l][r].has_value()) return memo[l][r].value();
    
    int res = 0;
    
    for (int idx2 = idx + 1; idx2 < N && lines[idx2].first < r; ++idx2) {
        
        if (lines[idx2].first > l && lines[idx2].second < r) {
            
            res = std::max(res, 1 + subSolve(lines[idx2].first, lines[idx2].second, idx2) + subSolve(lines[idx2].second, r, idx2));
        }
    }
    
    return (memo[l][r] = res).value();
}

void solve() {
    
    int res = 0;
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (lines[idx].second < 100) {
            
            res = std::max(res, 1 + subSolve(lines[idx].first, lines[idx].second, idx) + subSolve(lines[idx].second, lines[idx].first + 100, idx));
        }
    }
    
    std::cout << res;
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    get_input();
    
    solve();
    
    return 0;
}

