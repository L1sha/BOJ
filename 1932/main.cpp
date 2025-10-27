#include "bits/stdc++.h"


int N;
std::array<std::array<int, 501>, 501> tri;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int temp;
    
    std::cin >> N >> tri[0][0];
    
    for (int idx = 1; idx < N; ++idx){
        
        std::cin >> temp;
        tri[idx][0] = temp + tri[idx - 1][0];
        
        for (int idx2 = 1; idx2 < idx; ++idx2){
            
            std::cin >> temp;
            tri[idx][idx2] = temp + (tri[idx - 1][idx2 - 1] > tri[idx - 1][idx2] ? tri[idx - 1][idx2 - 1] : tri[idx - 1][idx2]);
        }
        
        std::cin >> temp;
        tri[idx][idx] = temp + tri[idx - 1][idx - 1];
    }
    
    std::cout << *std::max_element(tri[N - 1].begin(), tri[N - 1].begin() + N);
    
    return 0;
}


