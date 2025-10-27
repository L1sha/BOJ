#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N;

std::vector<int> LIS;
std::array<intPair, 100'001> lines;
std::array<std::vector<int>, 100'001> candidateIdx;
std::array<int, 100'001> realLIS;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> lines[idx].first >> lines[idx].second;
    
    std::sort(lines.begin(), lines.begin() + N);
    
    LIS.push_back(lines[0].second);
    candidateIdx[0].push_back(0);
    
    int ans = 1, lowerBoundIdx, temp;
    
    for (int idx = 1; idx < N ; ++idx){
        
        temp = lines[idx].second;
        
        if (LIS.back() < temp) { 
            
            LIS.push_back(temp);
            candidateIdx[ans++].push_back(idx);
        }
        else {
            
            lowerBoundIdx = std::distance(LIS.begin(), std::lower_bound(LIS.begin(), LIS.end(), temp));
            LIS[lowerBoundIdx] = temp;
            candidateIdx[lowerBoundIdx].push_back(idx);
        }
    }
    
    temp = candidateIdx[ans - 1].back();
    realLIS[ans - 1] = lines[temp].first;
    
    for (int idx = ans - 2; idx >= 0; --idx){
        
        temp = *(std::lower_bound(candidateIdx[idx].begin(), candidateIdx[idx].end(), temp) - 1);
        realLIS[idx] = lines[temp].first;
    }
    
    std::cout << N - ans << '\n';
    
    temp = 0;
    for (int idx = 0; idx < N; ++idx) {
        
        if (lines[idx].first == realLIS[temp]) temp++;
        else std::cout << lines[idx].first << '\n';
    }
    
    
    return 0;
}