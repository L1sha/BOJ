#include "bits/stdc++.h"

using intPair = std::pair<int, int>;

int N, M;

std::vector<intPair> home;
std::vector<intPair> chicken;


int dist(intPair& a, intPair& b){
    
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

int count(int bitMask) {
    
    int cnt = 0;
    while (bitMask) {
        
        cnt += (bitMask % 2);
        bitMask /= 2;
    }
    return cnt;
}

int solve(int bitMask) {
    
    int res = 0, temp, min, idx;
    
    for (auto& el : home){
        
        min = 1e9;
        idx = 0;
        temp = bitMask;
        
        while (temp){
            
            if (temp % 2){
                
                min = std::min(min, dist(el, chicken[idx]));
            }
            
            temp /= 2;
            idx++;
        }
        
        res += min;
    }
    
    return res;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    int temp;
    
    for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < N; ++idx2){
        
        std::cin >> temp;
        if (temp == 1) home.push_back({idx, idx2});
        else if (temp == 2) chicken.push_back({idx, idx2});
    }
    
    int min = 1e9;
    
    for (int bitMask = 0; bitMask < (1 << chicken.size()); ++bitMask){
        
        if (count(bitMask) != M) continue;
        min = std::min(min, solve(bitMask));
    }
    
    std::cout << min;
    
    return 0;
}



