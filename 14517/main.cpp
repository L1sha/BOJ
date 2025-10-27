#include "bits/stdc++.h"


std::array<std::array<std::optional<int>, 1000>, 1000> memo;
std::string s;
const int PRIME = 10'007;

int countPalindrome(int start, int end) {
    
    if (start > end) {
        
        return 0;
    }
    
    if (start == end) {
        
        return 1;
    }
    
    if (memo[start][end].has_value()) {
        
        return memo[start][end].value();
    }
    
    int res = countPalindrome(start, end - 1);
    
    for (int cursor = start; cursor <= end; ++cursor) {
        
        if (s[cursor] == s[end]) {
            
            res++;
            res += countPalindrome(cursor + 1, end - 1);
        }
    }
    
    return (memo[start][end] = res % PRIME).value();
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> s;
    
    std::cout << countPalindrome(0, s.size() - 1);
    
    return 0;
}

