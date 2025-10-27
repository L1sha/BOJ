#include "bits/stdc++.h"


constexpr int N_MAX = 100'001, A_MAX = 100'001, M_MAX = 100'000;

int N, sqrtN, M;

struct Query {
    
    int s, e, idx;
    bool operator< (const Query& rhs) {
        
        if (s / sqrtN == rhs.s / sqrtN) return e < rhs.e;
        return s / sqrtN < rhs.s / sqrtN;
    }
};

std::array<int, N_MAX> A;
std::array<int, A_MAX> cnt;
std::array<int, N_MAX> ccnt;
std::array<Query, M_MAX> queries;
std::array<int, M_MAX> res;

void get_input() {
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> A[idx];
    
    std::cin >> M;
    
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> queries[idx].s >> queries[idx].e;
        queries[idx].idx = idx;
    }
}

void solve() {
    
    sqrtN = sqrt(N);
    
    std::sort(queries.begin(), queries.begin() + M);
    
    int s = queries[0].s, e = queries[0].e, ans = 0;
    
    ccnt[0] = N;
    
    for (int idx = s; idx <= e; ++idx) {
        
        --ccnt[cnt[A[idx]]];
        ++ccnt[++cnt[A[idx]]];
        ans = std::max(ans, cnt[A[idx]]);
    }
    res[queries[0].idx] = ans;
    
    for (int idx = 1; idx < M; ++idx) {
        
        while (s < queries[idx].s) {
            
            if (ans == cnt[A[s]] && ccnt[ans] == 1) --ans;
            --ccnt[cnt[A[s]]--];
            ++ccnt[cnt[A[s++]]];
        }
        
        while (s > queries[idx].s) {
            
            --ccnt[cnt[A[--s]]];
            ++ccnt[++cnt[A[s]]];
            ans = std::max(ans, cnt[A[s]]);
        }
        
        while (e < queries[idx].e) {
            
            --ccnt[cnt[A[++e]]];
            ++ccnt[++cnt[A[e]]];
            ans = std::max(ans, cnt[A[e]]);
        }
        
        while (e > queries[idx].e) {
            
            if (ans == cnt[A[e]] && ccnt[ans] == 1) --ans;
            --ccnt[cnt[A[e]]--];
            ++ccnt[cnt[A[e--]]];
        }
        
        res[queries[idx].idx] = ans;
    }
    
    for (int idx = 0; idx < M; ++idx) std::cout << res[idx] << '\n';
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    get_input();
    
    solve();
    
    return 0;
}

