#include "bits/stdc++.h"

constexpr int N_MAX = 1000;

int N;
std::vector<std::string> nums;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

bool myComp(const std::string& left, const std::string& right) {
    
    std::string L = left + right, R = right + left;
    return L > R;
}

void get_input() {
    
    std::cin >> N;
    nums.resize(N);
    
    for (auto& el : nums) std::cin >> el;
}

void solve() {
    
    std::sort(nums.begin(), nums.end(), myComp);
    
    if (nums.front() == "0") std::cout << "0";
    else for (const auto& el : nums) std::cout << el;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}