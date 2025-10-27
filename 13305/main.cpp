#include "bits/stdc++.h"


int N;
std::array<int, 100'001> dist;
std::array<int, 100'001> price;




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N - 1; ++idx) std::cin >> dist[idx];
    for (int idx = 0; idx < N; ++idx) std::cin >> price[idx];
    
    int cursor = 0, min = 1'000'000'001;
    long long res = 0, temp = 0;
    
    while (cursor != N - 1){
        
        if (price[cursor] > min){
            
            temp += dist[cursor];
            cursor++;
        }
        else {
            
            res += temp * min;
            temp = dist[cursor];
            min = price[cursor];
            cursor++;
        }
    }
    
    res += temp * min;
    
    std::cout << res;
    
    return 0;
}


