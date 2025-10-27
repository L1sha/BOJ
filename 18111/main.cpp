#include "bits/stdc++.h"


int N, M, B;

std::array<std::array<int, 501>, 501> heights;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> B;
    
    int min = 256, max = 0;
    
    for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < M; ++idx2){
        
        std::cin >> heights[idx][idx2];
        if (heights[idx][idx2] > max) max = heights[idx][idx2];
        if (heights[idx][idx2] < min) min = heights[idx][idx2];
    }
    
    int resTime = 500 * 500 * 256 * 2, resHeight, temp, b;
    
    for (int h = min; h <= max; ++h){
        
        temp = 0;
        b = B;
        
        for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < M; ++idx2){
            
            if (heights[idx][idx2] > h) { temp += (heights[idx][idx2] - h) * 2; b += (heights[idx][idx2] - h); }
            if (heights[idx][idx2] < h) { temp -= (heights[idx][idx2] - h); b += (heights[idx][idx2] - h); }
        }
        
        if (b >= 0 && temp <= resTime) { resTime = temp; resHeight = h; }
    }
    
    std::cout << resTime << ' ' << resHeight;
    
    return 0;
}


