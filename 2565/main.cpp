#include "bits/stdc++.h"


int N;
std::array<std::pair<int, int>, 101> lines;
std::array<int, 101> max;
std::array<int, 101> num;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> lines[idx].first >> lines[idx].second;
    std::sort(lines.begin(), lines.begin() + N);
    
    for (int idx = 0; idx < N; ++idx) num[idx] = lines[idx].second;
    
    for (int idx = 0; idx < N; ++idx){
        
        max[idx] = 1;
        for (int idx2 = 0; idx2 < idx; ++idx2) if (max[idx2] >= max[idx] && num[idx] > num[idx2]) max[idx] = max[idx2] + 1;
    }
    
    std::cout << N - *std::max_element(max.begin(), max.begin() + N);
    
    
    return 0;
}


