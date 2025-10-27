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
    
    std::vector<int> A, B;
    A.reserve(N);
    B.reserve(N);
    
    while (N >= 3) {
        
        A.push_back(N);
        B.push_back(N - 1);
        B.push_back(N - 2);
        N -= 3;
    }
    
    if (N == 2) {
        
        A.push_back(2);
        B.push_back(1);
    }
    
    std::cout << A.size() << '\n';
    for (const auto& el : A) std::cout << el << ' ';
    std::cout << '\n' << B.size() << '\n';
    for (const auto& el : B) std::cout << el << ' ';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}