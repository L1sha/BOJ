#include "bits/stdc++.h"


int N;

std::array<int, 1001> A;
std::array<int, 1001> res;
std::array<std::vector<int>, 1001> res2;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int temp;
    
    for (int idx = 0; idx < N; ++idx){
        
        std::cin >> A[idx];
        
        temp = idx;
        res[idx] = 1;
        
        for (int idx2 = 0; idx2 < idx; ++idx2) if (A[idx2] < A[idx] && res[idx2] >= res[idx]){
            
            res[idx] = res[idx2] + 1;
            temp = idx2;
        }
        
        res2[idx].insert(res2[idx].begin(), res2[temp].begin(), res2[temp].end());
        res2[idx].insert(res2[idx].end(), A[idx]);
    }
    
    int ans = std::distance(res.begin(), std::max_element(res.begin(), res.begin() + N));
    
    std::cout << res[ans] << '\n';
    for (auto &el : res2[ans]) std::cout << el << ' ';
    
    return 0;
}


