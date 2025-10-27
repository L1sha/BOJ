#include "bits/stdc++.h"

int A_MAX, C_MAX;

std::string A, B, C; 

std::vector<std::vector<std::optional<bool>>> dp;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> A >> B >> C;
    
    C_MAX = C.size();
    A_MAX = A.size();
    
    dp.clear();
    dp.resize(C_MAX, std::vector<std::optional<bool>>(A_MAX + 1));
}

bool solve(int cCursor = 0, int aCursor = 0) {
    
    if (cCursor == C_MAX) return true;
    
    if (dp[cCursor][aCursor].has_value()) return dp[cCursor][aCursor].value();
    
    if (aCursor != A_MAX && A[aCursor] == C[cCursor]) {
        
        if (solve(cCursor + 1, aCursor + 1)) {
            
            return (dp[cCursor][aCursor] = true).value();
        }
    }
    
    if (cCursor - aCursor != C_MAX - A_MAX && B[cCursor - aCursor] == C[cCursor]) {
        
        if (solve(cCursor + 1, aCursor)) {
            
            return (dp[cCursor][aCursor] = true).value();
        }
    }
    
    return (dp[cCursor][aCursor] = false).value();
}



int main(int argc, char** argv) {
    
    fastIO();
    
    int T; std::cin >> T;
    for (int idx = 1; idx <= T; ++idx) {
        
        get_input();
        
        std::cout << "Data set " << idx << ": ";
        if (solve()) std::cout << "yes\n";
        else std::cout << "no\n";
    }
    
    return 0;
}

