#include "bits/stdc++.h"

constexpr int N_MAX = 1'000'000;

int N;

std::vector<std::tuple<int, int, int>> gain, same, loss;
int noChangeMax = 0;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    std::string s;
    
    for (int before, after, curr, idx = 1; idx <= N; ++idx) {
        
        std::cin >> s;
        
        before = 0, after = 0, curr = 0;
        
        for (const auto& c : s) {
            
            if (c == '(') ++curr;
            else {
                
                --curr;
                before = std::max(before, -curr);
            }
        }
        
        after = curr + before;
        
        if (before < after) gain.push_back({before, after, idx});
        else if (before == after) {
            
            noChangeMax = std::max(noChangeMax, before);
            same.push_back({before, after, idx});
        }
        else loss.push_back({before, after, idx});
    }
}

void solve() {
    
    long long capacity = 0;
    
    std::sort(gain.begin(), gain.end(), std::less<>());
    
    for (const auto& [before, after, idx] : gain) {
        
        if (capacity < before) {
            
            std::cout << "impossible";
            return;
        }
        else {
            
            capacity += (after - before);
        }
    }
    
    if (capacity < noChangeMax) {
        
        std::cout << "impossible";
        return;
    }
    
    std::sort(loss.begin(), loss.end(),
    [](const std::tuple<int, int, int>& left, const std::tuple<int, int, int>& right){
        
        auto& [l1, l2, l3] = left;
        auto& [r1, r2, r3] = right;
        
        return l2 > r2;
    });
    
    for (const auto& [before, after, idx] : loss) {
        
        if (capacity < before) {
            
            std::cout << "impossible";
            return;
        }
        else {
            
            capacity -= (before - after);
        }
    }
    
    if (capacity != 0) {
        
        std::cout << "impossible";
        return;
    }
    
    for (const auto& [before, after, idx] : gain) std::cout << idx << '\n';
    for (const auto& [before, after, idx] : same) std::cout << idx << '\n';
    for (const auto& [before, after, idx] : loss) std::cout << idx << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}