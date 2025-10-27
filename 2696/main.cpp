#include "bits/stdc++.h"

int T, N;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
}

void solve() {
    
    std::priority_queue<int> small;
    std::priority_queue<int, std::vector<int>, std::greater<>> big;
    
    std::cout << (N + 1) / 2 << '\n';
    
    int input;
    std::cin >> input;
    std::cout << input << ' ';
    big.push(input);
    
    for (int idx = 2; idx <= N; ++idx) {
        
        std::cin >> input;
        
        if (idx & 1) {
            
            if (input < small.top()) {
                
                big.push(small.top());
                small.pop();
                small.push(input);
            }
            else big.push(input);
            
            std::cout << big.top() << ' ';
            if (idx % 20 == 19) std::cout << '\n';
        }
        else {
            
            if (input > big.top()) {
                
                small.push(big.top());
                big.pop();
                big.push(input);
            }
            else small.push(input);
        }
    }
    
    std::cout << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    std::cin >> T;
    while (T--) {
        
        get_input();
        solve();
    }
    
    return 0;
}

