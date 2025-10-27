#include "bits/stdc++.h"


int N, res, min, max;
std::array<std::pair<int, int>, 1'000'000> lines;



int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> lines[idx].first >> lines[idx].second;
    }
    
    std::sort(lines.begin(), lines.begin() + N);
    
    min = lines[0].first;
    max = lines[0].second;
    
    for (int idx = 1; idx < N; ++idx) {
        
        if (lines[idx].first > max) {
            
            res += (max - min);
            
            min = lines[idx].first;
            max = lines[idx].second;
        }
        else {
            
            max = std::max(lines[idx].second, max);
        }
    }
    
    res += (max - min);
    
    std::cout << res;
    
    return 0;
}

