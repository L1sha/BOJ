#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;

int T, N;
std::string query;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void solve() {
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> query >> N;
        
        std::deque<int> dq;
        int temp = 0;
        char c;
        bool rev = false, errorFlag = false;
        
        std::cin >> c;
        
        while (true) {
            
            std::cin >> c;
            
            if (c == ',') {
                
                dq.push_back(temp);
                temp = 0;
            }
            else if (c == ']') {
                
                if (temp) dq.push_back(temp);
                break;
            }
            else {
                
                temp *= 10;
                temp += (int)(c - '0');
            }
        }
        
        for (const auto& el : query) {
            
            if (el == 'R') rev = !rev;
            else {
                
                if (dq.size() == 0) {
                    
                    errorFlag = true;
                    break;
                }
                
                if (rev) dq.pop_back();
                else dq.pop_front();
            }
        }
        
        if (errorFlag) std::cout << "error\n";
        else {
            
            if (dq.empty()) std::cout << '[';
            
            if (rev) {
                
                for (auto it = dq.rbegin(); it != dq.rend(); ++it) {
                
                    if (it == dq.rbegin()) std::cout << '[';
                    else std::cout << ',';
                    std::cout << *it;
                }
            }
            else {
                
                for (auto it = dq.begin(); it != dq.end(); ++it) {
                
                    if (it == dq.begin()) std::cout << '[';
                    else std::cout << ',';
                    std::cout << *it;
                }
            }
            
            std::cout << ']' << '\n';
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    solve();
    
    return 0;
}

