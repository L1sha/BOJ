#include "bits/stdc++.h"

int N, K;

std::deque<int> nums;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K;
    nums.resize(K);
    for (auto& el : nums) std::cin >> el;
}

void solve() {
    
    if (!nums.empty() && nums.front() == 1) nums.pop_front();
    else nums.push_front(1);
    
    std::cout << N << ' ' << nums.size() << std::endl;
    for (const auto& el : nums) std::cout << el << ' ';
    std::cout << std::endl;
}



int main(int argc, char** argv) {
    
    fastIO();
    int T; std::cin >> T;
    while (T--) {
        
        get_input();
        solve();
    }
    
    return 0;
}