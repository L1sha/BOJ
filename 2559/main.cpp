#include "bits/stdc++.h"


int N, K;
 




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    std::vector<int> partial(N - K + 1);
    std::queue<int> q;
    int temp, sum = 0;
    
    for (int idx = 0; idx < K; ++idx){
        
        std::cin >> temp;
        q.push(temp);
        sum += temp;
    }
    
    partial[0] = sum;
    
    for (int idx = 1; idx <= N - K; ++idx){
        std::cin >> temp;
        
        sum -= q.front();
        q.pop();
        sum += temp;
        q.push(temp);
        
        partial[idx] = sum;
    }
    
    std::cout << *std::max_element(partial.begin(), partial.end());
    
    
    
    return 0;
}


