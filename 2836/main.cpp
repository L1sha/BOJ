#include "bits/stdc++.h"


constexpr int N_MAX = 300'000, M_MAX = 1e9;

int N, M, from, to;
std::vector<std::pair<int, int>> backward;

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    while (N--) {
        
        std::cin >> from >> to;
        
        if (from > to) {
            
            backward.push_back({from, to});
        }
    }
    
    std::sort(backward.begin(), backward.end(), std::greater<std::pair<int, int>>());
    
    long long add = 0;
    
    if (!backward.empty()) {
        
        int max = backward.front().first, min = backward.front().second;
        
        for (auto it = backward.begin() + 1; it != backward.end(); ++it) {
            
            if ((*it).first < min) {
                
                add += (max - min);
                max = (*it).first;
            }
            
            min = std::min(min, (*it).second);
        }
        
        add += (max - min);
    }
    
    std::cout << add * 2 + M;
    
    return 0;
}

