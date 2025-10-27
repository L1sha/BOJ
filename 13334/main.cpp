#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, D;

std::array<intPair, 100'000> sortByFirst;
std::array<intPair, 100'000> sortBySecond;


bool compareBySecond(const intPair a, const intPair b) {
        
    if (a.second < b.second) {
        
        return true;
    }
    else if (a.second == b.second) {
        
        if (a.first < b.first) {
            
            return true;
        }
    }
    
    return false;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> sortByFirst[idx].first >> sortByFirst[idx].second;
    }
    
    int cnt = 0;
    
    std::cin >> D;
    for (int idx = 0; idx < N; ++idx) {
        
        if (sortByFirst[idx].first > sortByFirst[idx].second) {
            
            std::swap(sortByFirst[idx].first, sortByFirst[idx].second);
        }
        
        if (sortByFirst[idx].second - sortByFirst[idx].first > D) {
            
            sortByFirst[idx] = { 2e9, 2e9 };
            cnt++;
        }
        else {
            
            sortBySecond[idx - cnt] = sortByFirst[idx];
        }
    }
    
    if (cnt == N) {
        
        std::cout << 0;
        return 0;
    }
    
    std::sort(sortByFirst.begin(), sortByFirst.begin() + N);
    
    N -= cnt;
    
    std::sort(sortBySecond.begin(), sortBySecond.begin() + N, compareBySecond);
    
    int left = 0, right = std::distance(sortBySecond.begin(), std::upper_bound(sortBySecond.begin(), sortBySecond.begin() + N, sortByFirst.front(), compareBySecond));
    int temp = right, res = right;
    
    while (right != N) {
        
        if (sortBySecond[right].second - sortByFirst[left].first <= D) {
            
            temp++;
            res = std::max(res, temp);
            
            right++;
        }
        else {
            
            temp--;
            
            left++;
        }
    }
    
    std::cout << res;
    
    return 0;
}

