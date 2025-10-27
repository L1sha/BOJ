#include "bits/stdc++.h"

// https://gumgood.github.io/suffix-array-and-lcp
// suffixArray : O(Nlog^2(N)) <= can be O(NlogN)
// LCPArray : O(N) <= Not my code, but awesome

constexpr int N_MAX = 500'000;

int N;
std::string S;

std::array<int, N_MAX> suffixArray, LCPArray, rank;
std::array<std::pair<int, int>, N_MAX> rankPair;

bool compByRankPair(const int& idx1, const int& idx2) {
    
    return rankPair[idx1] < rankPair[idx2];
}

void fillRank() {
    
    int cnt = 0;
    
    rank[suffixArray[0]] = cnt;
    
    for (int idx = 1; idx < N; ++idx) {
        
        if (rankPair[suffixArray[idx - 1]] != rankPair[suffixArray[idx]]) cnt++;
        
        rank[suffixArray[idx]] = cnt;
    }
}

void fillRankPair(const int& pow2) {
    
    int nextRank;
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (idx + pow2 >= N) nextRank = -1;
        else nextRank = rank[idx + pow2];
        
        rankPair[idx] = {rank[idx], nextRank};
    }
}

void getSuffixArray() {
    
    for (int idx = 0; idx < N; ++idx) {
        
        suffixArray[idx] = idx;
        rankPair[idx] = {S[idx] - 'a', 0};
    }
    
    std::sort(suffixArray.begin(), suffixArray.begin() + N, compByRankPair);
    fillRank();
    
    int pow2 = 1;
    
    for (int pow2 = 1; pow2 < N; pow2 <<= 1) {
        
        fillRankPair(pow2);
        std::sort(suffixArray.begin(), suffixArray.begin() + N, compByRankPair);
        fillRank();
    }
    
    for (int idx = 0; idx < N; ++idx) std::cout << suffixArray[idx] + 1 << ' ';
    std::cout << '\n';
}

void getLCPArray() {
    
    std::vector<int> inverseSuffixArray(N);
    
    for (int idx = 0; idx < N; ++idx) inverseSuffixArray[suffixArray[idx]] = idx;
    
    for (int k = 0, idx = 0; idx < N; ++idx) {
        
        if (inverseSuffixArray[idx] > 0) {
            
            for (int idx2 = suffixArray[inverseSuffixArray[idx] - 1]; S[idx2 + k] == S[idx + k]; ++k);
            
            LCPArray[inverseSuffixArray[idx]] = (k ? k-- : 0);
        }
    }
    
    std::cout << "x ";
    for (int idx = 1; idx < N; ++idx) std::cout << LCPArray[idx] << ' ';
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> S;
    N = S.size();
    
    getSuffixArray();
    
    getLCPArray();
    
    return 0;
}

