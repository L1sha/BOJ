#include "bits/stdc++.h"


int N;

std::array<int, 1001> RR;
std::array<int, 1001> RG;
std::array<int, 1001> RB;
std::array<int, 1001> GR;
std::array<int, 1001> GG;
std::array<int, 1001> GB;
std::array<int, 1001> BR;
std::array<int, 1001> BG;
std::array<int, 1001> BB;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int R, G, B;
    
    std::cin >> R >> G >> B;
    
    RR[2] += R;
    RG[2] += R;
    RB[2] += R;
    GR[2] += G;
    GG[2] += G;
    GB[2] += G;
    BR[2] += B;
    BG[2] += B;
    BB[2] += B;
    
    std::cin >> R >> G >> B;
    
    RR[2] += 1e9;
    RG[2] += G;
    RB[2] += B;
    GR[2] += R;
    GG[2] += 1e9;
    GB[2] += B;
    BR[2] += R;
    BG[2] += G;
    BB[2] += 1e9;
    
    for (int idx = 3; idx <= N; ++idx) {
        
        std::cin >> R >> G >> B;
        
        RR[idx] = std::min(RG[idx - 1], RB[idx - 1]) + R;
        RG[idx] = std::min(RR[idx - 1], RB[idx - 1]) + G;
        RB[idx] = std::min(RR[idx - 1], RG[idx - 1]) + B;
        GR[idx] = std::min(GG[idx - 1], GB[idx - 1]) + R;
        GG[idx] = std::min(GR[idx - 1], GB[idx - 1]) + G;
        GB[idx] = std::min(GR[idx - 1], GG[idx - 1]) + B;
        BR[idx] = std::min(BG[idx - 1], BB[idx - 1]) + R;
        BG[idx] = std::min(BR[idx - 1], BB[idx - 1]) + G;
        BB[idx] = std::min(BR[idx - 1], BG[idx - 1]) + B;
    }
    
    int min = std::min(RG[N], RB[N]);
    min = std::min(min, GR[N]);
    min = std::min(min, GB[N]);
    min = std::min(min, BR[N]);
    min = std::min(min, BG[N]);
    
    std::cout << min;
    
    return 0;
}


