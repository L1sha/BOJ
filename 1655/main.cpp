#include "bits/stdc++.h"


int N;

std::priority_queue<int> down;
std::priority_queue<int, std::vector<int>, std::greater<int>> up;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
}

void solve() {
    
    for (int input; N--; ) {
        
        std::cin >> input;
        
        if (up.size() == down.size()) {
            
            if (down.size() && input < down.top()) {
                
                up.push(down.top());
                down.pop();
                down.push(input);
            }
            else up.push(input);
            
            std::cout << up.top() << '\n';
        }
        else {
            
            if (input > up.top()) {
                
                down.push(up.top());
                up.pop();
                up.push(input);
            }
            else down.push(input);
            
            std::cout << down.top() << '\n';
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

