#include "bits/stdc++.h"

constexpr int N_MAX = 100'000, T_MAX = 100'000, A_MAX = 1'000'001;

int N, T, sqrtN;

struct Query {
    
    int idx, l, r;
    
    bool operator< (const Query& rhs) {
        
        if (l / sqrtN == rhs.l / sqrtN) return r < rhs.r;
        return l / sqrtN < rhs.l / sqrtN;
    }
};

std::array<long long, N_MAX> A;
std::array<Query, T_MAX> queries;
std::array<int, A_MAX> cnt;
std::array<long long, T_MAX> res;
std::bitset<A_MAX> exceptional;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> T;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> A[idx];
    
    for (int idx = 0; idx < T; ++idx) {
        
        queries[idx].idx = idx;
        std::cin >> queries[idx].l >> queries[idx].r;
        queries[idx].l--;
        queries[idx].r--;
    }
}

void solve() {
    
    sqrtN = sqrt(N);
    
    std::sort(queries.begin(), queries.begin() + T);
    
    long long power = 0, realPower;
    
    for (int prev = -1, l, r, intervalL, intervalR, idx = 0; idx < T; ++idx) {
        
        if (queries[idx].l / sqrtN != prev) {
            
            for (int cursor = 0; cursor < N; ++cursor) {
                
                cnt[A[cursor]] = 0;
                exceptional[A[cursor]] = false;
            }
            prev = queries[idx].l / sqrtN;
            power = 0;
            
            l = queries[idx].l;
            r = queries[idx].r;
            intervalL = prev * sqrtN;
            intervalR = std::min((prev + 1) * sqrtN, N) - 1;
            
            for (int cursor = intervalL; cursor <= intervalR; ++cursor) exceptional[A[cursor]] = true;
            
            for (int cursor = l; cursor <= r; ++cursor) {
                
                cnt[A[cursor]]++;
                
                if (!exceptional[A[cursor]]) power += A[cursor] * (cnt[A[cursor]] * 2 - 1);
            }
        }
        else {
            
            while (l < queries[idx].l) cnt[A[l++]]--;
            
            while (l > queries[idx].l) cnt[A[--l]]++;
            
            while (r < queries[idx].r) {
                
                cnt[A[++r]]++;
                
                if (!exceptional[A[r]]) power += A[r] * (cnt[A[r]] * 2 - 1);
            }
        }
        
        realPower = power;
        
        for (int cursor = intervalL; cursor <= intervalR; ++cursor) exceptional[A[cursor]] = false;
        
        for (int cursor = intervalL; cursor <= intervalR; ++cursor) {
            
            if (!exceptional[A[cursor]]) {
                
                exceptional[A[cursor]] = true;
                realPower += (A[cursor] * cnt[A[cursor]]) * cnt[A[cursor]];
            }
        }
        
        res[queries[idx].idx] = realPower;
    }
    
    for (int idx = 0; idx < T; ++idx) std::cout << res[idx] << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

