#include "bits/stdc++.h"


int N, S;

std::array<int, 100'001> partialSum;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> S;
    
    int temp;
    
    for (int idx = 0; idx < N; ++idx) { std::cin >> temp; partialSum[idx + 1] = partialSum[idx] + temp; } 
    
    
    int res = 1e9;
    
    for (auto it = std::lower_bound(partialSum.begin(), partialSum.begin() + N + 1, S); it != partialSum.begin() + N + 1; ++it) {
        
        auto it2 = std::lower_bound(partialSum.begin(), it, *it - S);
        if (*it2 > *it - S) it2--;
        temp = std::distance(it2, it);
        res = std::min(temp, res);
    }
    
    if (res == 1e9) res = 0;
    
    std::cout << res;
    
    return 0;
}


