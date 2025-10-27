#include "bits/stdc++.h"


constexpr int N_MAX = 2'000'000;

int N;

std::string S;
std::array<char, N_MAX * 2> S2;
std::array<int, N_MAX * 2> A;


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> S;
    N = S.size();
    for (int idx = 0; idx < N; ++idx) {
        
        S2[idx * 2] = S[idx];
        S2[idx * 2 + 1] = '#';
    }
    N = 2 * N - 1;
    
    long long res = 0;
    
    for (int idx = 0, r = 0, p = 0; idx < N; ++idx) {
        
        if (r >= idx) A[idx] = std::min(A[2 * p - idx], r - idx);
        else A[idx] = 0;
        
        while (idx - A[idx] - 1 >= 0 && idx + A[idx] + 1 < N && S2[idx - A[idx] - 1] == S2[idx + A[idx] + 1]) A[idx]++;
        
        if (idx + A[idx] >= r) {
            
            r = idx + A[idx];
            p = idx;
        }
        
        res += (A[idx] + idx % 2) / 2 + (idx + 1) % 2;
    }
    
    std::cout << res;
    
    return 0;
}