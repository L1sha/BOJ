#include "bits/stdc++.h"


int N;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
}

void solve() {
    
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;
    
    for (int row = 0; row < N; ++row) {
        
        for (int input, col = 0; col < N; ++col) {
            
            std::cin >> input;
            pq.push(input);
        }
        
        while (pq.size() > N) pq.pop();
    }
    
    std::cout << pq.top();
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

