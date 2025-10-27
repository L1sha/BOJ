#include "bits/stdc++.h"


int N;
std::array<int, 1001> R;
std::array<int, 1001> G;
std::array<int, 1001> B;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int r, g, b;
    
    std::cin >> N >> R[0] >> G[0] >> B[0];
    
    for (int idx = 1; idx < N; ++idx){
        
        std::cin >> r >> g >> b;
        
        R[idx] = r + (G[idx - 1] < B[idx - 1] ? G[idx - 1] : B[idx - 1]);
        G[idx] = g + (B[idx - 1] < R[idx - 1] ? B[idx - 1] : R[idx - 1]);
        B[idx] = b + (R[idx - 1] < G[idx - 1] ? R[idx - 1] : G[idx - 1]);
    }
    
    int min = (R[N - 1] < G[N - 1] ? R[N - 1] : G[N - 1]);
    min = (min < B[N - 1] ? min : B[N - 1]);
    
    std::cout << min;

    return 0;
}


