#include "bits/stdc++.h"


int N, res, cnt;

std::array<int, 8> abilities;
std::array<int, 10> test;
std::array<bool, 7> used;

bool check() {
    
    test[8] = test[0];
    test[9] = test[1];
    
    double a, det, root2 = std::sqrt(2);
    
    for (int idx = 0; idx < 8; ++idx) {
        
        a = - (static_cast<double>(test[idx]) / test[idx + 2]);
        det = test[idx + 1] / root2 - a * (test[idx + 1] / root2) - test[idx];
        
        if (det < 0) return false;
    }
    
    return true;
}

void solve() {
    
    if (cnt == 7) {
        
        if (check()) res++;
        return;
    }
    
    for (int idx = 0; idx < 7; ++idx) {
        
        if (used[idx]) continue;
        
        test[cnt++] = abilities[idx];
        used[idx] = true;
        
        solve();
        
        cnt--;
        used[idx] = false;
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    for (auto& abil : abilities) std::cin >> abil;
    test[7] = abilities[7];
    
    solve();
    
    std::cout << res * 8;
    
    return 0;
}


