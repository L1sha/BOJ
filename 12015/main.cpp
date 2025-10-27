#include "bits/stdc++.h"


int N;

std::vector<int> LIS;
std::array<int, 1'000'001> A;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N ; ++idx){
        
        std::cin >> A[idx];
        
        if (LIS.empty() || LIS.back() < A[idx]) LIS.push_back(A[idx]);
        else *std::lower_bound(LIS.begin(), LIS.end(), A[idx]) = A[idx];
    }
    
    std::cout << LIS.size();
    
    return 0;
}


