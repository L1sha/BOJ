#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;

int N;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
}

std::pair<int, std::vector<int>> segInit(int cursor = 1, int l = 0, int r = N - 1) {
    
    if (r - l == 0) return {l, std::vector<int>()};
    
    char input;
    
    if (r - l == 1) {
        
        std::cout << "? " << l << ' ' << r << std::endl;
        std::cin >> input;
        
        if (input == '<') return {l, {r}};
        else return {r, {l}};
    }
    else {
        
        auto [lRes, lVec] = segInit(cursor * 2, l, l + (r - l) / 2);
        auto [rRes, rVec] = segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        std::cout << "? " << lRes << ' ' << rRes << std::endl;
        std::cin >> input;
        
        if (input == '<') {
            
            lVec.push_back(rRes);
            return {lRes, lVec};
        }
        else {
            
            rVec.push_back(lRes);
            return {rRes, rVec};
        }
    }
}

void solve() {
    
    auto [min, candidates] = segInit();
    char input;
    int res = 0;
    
    for (int idx = 1; idx < candidates.size(); ++idx) {
        
        std::cout << "? " << candidates[res] << ' ' << candidates[idx] << std::endl;
        std::cin >> input;
        
        if (input == '>') res = idx;
    }
    
    std::cout << "! " << candidates[res] << std::endl;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}