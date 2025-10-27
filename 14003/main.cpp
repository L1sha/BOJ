#include "bits/stdc++.h"


int N;

std::vector<int> LIS;
std::array<int, 1'000'001> A;
std::array<std::vector<int>, 1'000'001> candidateIdx;
std::vector<int> realLIS;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> A[0];
    LIS.push_back(A[0]);
    candidateIdx[0].push_back(0);
    
    int ans = 1;
    
    for (int idx = 1; idx < N ; ++idx){
        
        std::cin >> A[idx];
        
        if (LIS.back() < A[idx]) { 
            
            LIS.push_back(A[idx]);
            candidateIdx[ans++].push_back(idx);
        }
        else {
            
            int lowerBoundIdx = std::distance(LIS.begin(), std::lower_bound(LIS.begin(), LIS.end(), A[idx]));
            LIS[lowerBoundIdx] = A[idx];
            candidateIdx[lowerBoundIdx].push_back(idx);
        }
    }
    
    int temp = candidateIdx[ans - 1].back();
    
    realLIS.resize(ans);
    realLIS[ans - 1] = A[temp];
    
    for (int idx = ans - 2; idx >= 0; --idx){
        
        temp = *(std::lower_bound(candidateIdx[idx].begin(), candidateIdx[idx].end(), temp) - 1);
        realLIS[idx] = A[temp];
    }
    
    std::cout << ans << '\n';
    for (auto& el : realLIS) std::cout << el << ' ';
    
    
    return 0;
}



