#include "bits/stdc++.h"


int N;

std::deque<int> dq;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    while (N--) dq.push_front(N + 1);
    
    int temp;
    
    while (true){
        
        temp = dq.front();
        dq.pop_front();
        
        if (dq.empty()) break;
        
        temp = dq.front();
        dq.pop_front();
        dq.push_back(temp);
    }
    
    std::cout << temp;
    
    return 0;
}


