#include "bits/stdc++.h"

constexpr long long N_MAX = 1e18;

std::string s;
int N, K;

std::array<int, 10> cnt;
std::vector<int> res;
int totCnt;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> s >> K;
    N = s.length();
}

void DFS(int idx = 0, bool flag = false) {
    
    if (totCnt > K) return;
    if (idx == N) {
        
        if (totCnt == K) {
            
            for (const auto& el : res) std::cout << el;
            
            exit(0);
        }
        
        return;
    }
    if (flag) {
        
        if (N - idx < K - totCnt) return;
        
        if (cnt[0] == 0 && totCnt < K) {
            
            res.push_back(0);
            ++cnt[0];
            ++totCnt;
            ++idx;
        }
        
        int min = 0;
        while (cnt[min] == 0) ++min;
        
        while (N - idx > K - totCnt) {
            
            res.push_back(min);
            ++cnt[min];
            ++idx;
        }
        
        min = 0;
        
        while (N != idx) {
            
            while (cnt[min] != 0) ++min;
            
            res.push_back(min);
            ++cnt[min];
            ++totCnt;
            ++idx;
        }
        
        for (const auto& el : res) std::cout << el;
        
        exit(0);
    }
    
    int curr = static_cast<int>(s[idx] - '0');
    
    if (cnt[curr]++ == 0) ++totCnt;
    res.push_back(curr);
    DFS(idx + 1, false);
    res.pop_back();
    if (--cnt[curr] == 0) --totCnt;
    
    int cand1 = curr + 1;
    while (cand1 < 10 && cnt[cand1] != 0) ++cand1;
    int cand2 = curr + 1;
    while (cand2 < 10 && cnt[cand2] == 0) ++cand2;
    
    if (cand1 > cand2) std::swap(cand1, cand2);
    
    if (cand1 < 10) {
        
        if (cnt[cand1]++ == 0) ++totCnt;
        res.push_back(cand1);
        DFS(idx + 1, true);
        res.pop_back();
        if (--cnt[cand1] == 0) --totCnt;
    }
    
    if (cand2 < 10) {
        
        if (cnt[cand2]++ == 0) ++totCnt;
        res.push_back(cand2);
        DFS(idx + 1, true);
        res.pop_back();
        if (--cnt[cand2] == 0) --totCnt;
    }
}

void solve() {
    
    DFS(0, false);
    
    if (K > N) {
        
        std::cout << 10;
        
        K -= 2;
        
        for (int idx = 0; idx < K; ++idx) std::cout << idx + 2;
    }
    else {
        
        // K >= 2
        // if K = 1, 999...999 possible
        
        std::cout << 10;
        
        int idx = 2;
        K -= 2;
        
        while (N + 1 - idx > K) {
            
            std::cout << 0;
            ++idx;
        }
        
        for (int idx = 0; idx < K; ++idx) std::cout << idx + 2;
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}