#include "bits/stdc++.h"

constexpr int N_MAX = 1'000'000;

int N;

std::vector<std::pair<int, int>> gain, loss;
int noChangeMax = 0;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int before, after, idx = 0; idx < N; ++idx) {
        
        std::cin >> before >> after;
        
        if (before < after) gain.push_back({before, after});
        else if (before == after) noChangeMax = std::max(noChangeMax, before);
        else loss.push_back({before, after});
    }
}

void solve() {
    
    long long res = 0, capacity = 0;
    
    std::sort(gain.begin(), gain.end(), std::less<>());
    
    for (const auto& [before, after] : gain) {
        
        if (capacity < before) {
            
            res += (before - capacity);
            capacity = after;
        }
        else {
            
            capacity += (after - before);
        }
    }
    
    if (capacity < noChangeMax) {
        
        res += (noChangeMax - capacity);
        capacity = noChangeMax;
    }
    
    std::sort(loss.begin(), loss.end(),
    [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        
        return left.second > right.second;
    });
    
    for (const auto& [before, after] : loss) {
        
        if (capacity < before) {
            
            res += (before - capacity);
            capacity = after;
        }
        else {
            
            capacity -= (before - after);
        }
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}