#include "bits/stdc++.h"


constexpr int N_MAX = 100'001, M_MAX = 100'000;

int N, sqrtN, M;

struct Query{
    
    int s, e, idx;
    bool operator<(const Query& rhs) {
        
        if (s / sqrtN == rhs.s / sqrtN) return e < rhs.e;
        return s / sqrtN < rhs.s / sqrtN;
    }
};

std::array<int, N_MAX> A, cnt;
std::array<int, M_MAX> res;
std::array<Query, M_MAX> queries;
std::unordered_map<int, int> map;

void solve() {
    
    sqrtN = sqrt(N);
    
    std::sort(queries.begin(), queries.begin() + M);
    
    int s = queries[0].s, e = queries[0].e, currCnt = 0;
    
    for (int idx = s; idx <= e; ++idx) {
        
        if (cnt[A[idx]]++ == 0) currCnt++;
    }
    res[queries[0].idx] = currCnt;
    
    for (int idx = 1; idx < M; ++idx) {
        
        while (s < queries[idx].s) {
            
            if (--cnt[A[s++]] == 0) currCnt--;
        }
        
        while (s > queries[idx].s) {
            
            if (cnt[A[--s]]++ == 0) currCnt++;
        }
        
        while (e < queries[idx].e) {
            
            if (cnt[A[++e]]++ == 0) currCnt++;
        }
        
        while (e > queries[idx].e) {
            
            if (--cnt[A[e--]] == 0) currCnt--;
        }
        
        res[queries[idx].idx] = currCnt;
    }
    
    for (int idx = 0; idx < M; ++idx) std::cout << res[idx] << '\n';
}




int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1, temp, cnt = 0; idx <= N; ++idx) {
        
        std::cin >> temp;
        if (!map.count(temp)) map[temp] = cnt++;
        A[idx] = map[temp];
    }
    
    std::cin >> M;
    
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> queries[idx].s >> queries[idx].e;
        queries[idx].idx = idx;
    }
    
    solve();
    
    return 0;
}

