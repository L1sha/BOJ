#include "bits/stdc++.h"


int N, D;
std::array<long long, 100'001> K;
std::vector<int> positive;

long long minDist(int s, int e) {
    
    if (e - s <= D) {
        
        return 0;
    }
    
    long long res = LLONG_MIN;
    std::priority_queue<std::pair<long long, int>> pq;
    
    for (int idx = s + 1; idx <= s + D; ++idx) {
        
        pq.push({K[idx], idx});
        
        if (idx >= e - D) {
            
            res = std::max(res, K[idx]);
        }
    }
    
    for (int idx = s + D + 1; idx <= e - 1; ++idx) {
        
        while (true) {
            
            auto [score, pos] = pq.top();
            
            if (idx - pos <= D) {
                
                pq.push({score + K[idx], idx});
                
                if (idx >= e - D) {
                    
                    res = std::max(res, score + K[idx]);
                }
                
                break;
            }
            else {
                
                pq.pop();
            }
        }
    }
    
    return res;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> D;
    
    long long min = LLONG_MIN;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> K[idx];
        
        if (K[idx] > 0) {
            
            positive.push_back(idx);
        }
        else {
            
            min = std::max(min, K[idx]);
        }
    }
    
    if (positive.empty()) {
        
        std::cout << min;
        
        return 0;
    }
    
    long long cur = K[positive[0]], max = K[positive[0]], dist;
    int sz = positive.size();
    
    for (int idx = 1; idx < sz; ++idx) {
        
        dist = minDist(positive[idx - 1], positive[idx]);
        
        if (cur + dist > 0) {
            
            cur = cur + dist + K[positive[idx]];
        }
        else {
            
            cur = K[positive[idx]];
        }
        
        max = std::max(max, cur);
    }
    
    std::cout << max;
    
    return 0;
}

