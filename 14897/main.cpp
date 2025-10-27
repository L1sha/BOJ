#include "bits/stdc++.h"

constexpr int N_MAX = 1'000'000, Q_MAX = 1'000'000;

int N, Q, cnt, sqrtN;

struct Query {
    
    int idx, l, r;
    bool operator< (const Query& rhs) {
        
        if (l / sqrtN == rhs.l / sqrtN) {
            
            if ((l / sqrtN) % 2) return r > rhs.r;
            else return r < rhs.r;
        }
        return l / sqrtN < rhs.l / sqrtN;
    }
};

std::array<int, N_MAX> A;
std::unordered_map<int, int> map;
std::array<Query, Q_MAX> queries;
std::array<int, Q_MAX> res;
std::array<int, N_MAX> counts;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int input, idx = 0; idx < N; ++idx) {
        
        std::cin >> input;
        if (!map.count(input)) map[input] = cnt++;
        A[idx] = map[input];
    }
    
    std::cin >> Q;
    
    for (int idx = 0; idx < Q; ++idx) {
        
        queries[idx].idx = idx;
        std::cin >> queries[idx].l >> queries[idx].r;
        queries[idx].l--;
        queries[idx].r--;
    }
}

void solve() {
    
    sqrtN = sqrt(N);
    
    std::sort(queries.begin(), queries.begin() + Q);
    
    int l = queries[0].l, r = queries[0].r, ans = 0;
    
    for (int cursor = l; cursor <= r; ++cursor) {
        
        if (counts[A[cursor]]++ == 0) ans++;
    }
    
    res[queries[0].idx] = ans;
    
    for (int idx = 1; idx < Q; ++idx) {
        
        while (l < queries[idx].l) {
            
            if (--counts[A[l++]] == 0) ans--;
        }
        
        while (l > queries[idx].l) {
            
            if (counts[A[--l]]++ == 0) ans++;
        }
        
        while (r < queries[idx].r) {
            
            if (counts[A[++r]]++ == 0) ans++;
        }
        
        while (r > queries[idx].r) {
            
            if (--counts[A[r--]] == 0) ans--;
        }
        
        res[queries[idx].idx] = ans;
    }
    
    for (int idx = 0; idx < Q; ++idx) std::cout << res[idx] << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

