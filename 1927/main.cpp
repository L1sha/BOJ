#include "bits/stdc++.h"


int N;

std::priority_queue<int, std::vector<int>, std::greater<int>> pq;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int input;
    
    while (N--){
        
        std::cin >> input;
        
        if (input == 0){
            
            if (pq.empty()) std::cout << 0 << '\n';
            else { std::cout << pq.top() << '\n'; pq.pop(); }
        }
        else pq.push(input);
    }
    
    return 0;
}


