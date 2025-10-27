#include "bits/stdc++.h"


constexpr int N_MAX = 1'000'000;

int N;
std::string S;

std::array<int, N_MAX> suffixArray, LCPArray, reverseSuffixArray, rank;
std::array<std::pair<int, int>, N_MAX> rankPair;

void fillRank() {
    
    int cnt = 0;
    rank[suffixArray[0]] = cnt;
    auto prev = rankPair[suffixArray[0]];
    
    for (int idx = 1; idx < N; ++idx) {
        
        if (prev != rankPair[suffixArray[idx]]) {
            
            cnt++;
            prev = rankPair[suffixArray[idx]];
        }
        
        rank[suffixArray[idx]] = cnt;
    }
}

void fillRankPair(const int& pow2) {
    
    for (int idx = 0; idx < N; ++idx) {
        
        rankPair[idx].first = rank[idx];
        rankPair[idx].second = (idx + pow2 < N) ? rank[idx + pow2] : -1;
    }
}

bool compByRankPair(const int& A, const int& B) {
    
    return rankPair[A] < rankPair[B];
}

void getSuffixArray() {
    
    for (int idx = 0; idx < N; ++idx) {
        
        suffixArray[idx] = idx;
        rankPair[idx] = {S[idx] - 'a', 0};
    }
    
    std::sort(suffixArray.begin(), suffixArray.begin() + N, compByRankPair);
    
    for (int pow2 = 1; pow2 < N; pow2 <<= 1) {
        
        fillRank();
        fillRankPair(pow2);
        std::sort(suffixArray.begin(), suffixArray.begin() + N, compByRankPair);
    }
}

void getLCPArray() {
    
    for (int idx = 0; idx < N; ++idx) reverseSuffixArray[suffixArray[idx]] = idx;
    
    for (int idx = 0, checked = 0; idx < N; ++idx) {
        
        if (reverseSuffixArray[idx] == 0) continue;
        
        for (int idx2 = suffixArray[reverseSuffixArray[idx] - 1]; S[idx2 + checked] == S[idx + checked]; checked++);
        
        LCPArray[reverseSuffixArray[idx]] = checked ? checked-- : 0;
    }
}

long long solve() {
    
    long long res = N - reverseSuffixArray[0];
    
    for (int idx = 1; idx < N; ++idx) res += N - reverseSuffixArray[idx] - LCPArray[idx];
    
    return res;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> S;
    N = S.size();
    
    getSuffixArray();
    
    getLCPArray();
    
    std::cout << solve();
    
    return 0;
}

