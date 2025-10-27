#include "bits/stdc++.h"


int N;
std::string s;
std::array<int, 1'000'001> KMP;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> s;
    
    int cursor = 0; 
    
    for (int idx = 2; idx <= N; ++idx) {
        
        if (s[cursor] == s[idx - 1]) {
            
            KMP[idx] = ++cursor; 
        }
        else {
            
            if (cursor == 0) {
                
                continue;
            }
            
            cursor = KMP[cursor];
            idx--;
        }
    }
    
    std::cout << N - KMP[N];
    
    return 0;
}

