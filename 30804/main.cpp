#include <iostream>
#include <array>

std::array<int, 200'000> S;
std::array<int, 10> cnt;
int cnts, N;

int main() {
    
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> S[idx];
    
    int l = 0, r = 0, res = 0;
    cnts = 1;
    cnt[S[0]]++;
    
    while (l < N && r < N) {
        
        if (cnts <= 2) {
            
            res = std::max(res, r - l + 1);
            if (cnt[S[++r]]++ == 0) cnts++;
        }
        else {
            
            if (--cnt[S[l++]] == 0) cnts--;
        }
    }
    
    std::cout << res;
    return 0;
}