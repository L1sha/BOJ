#include "bits/stdc++.h"

constexpr int N_MAX = 300'000, C_MAX = 10'000, M_MAX = 10'000;

int N, C, M, sqrtN;

struct Query {
    
    int idx, l, r;
    
    bool operator< (const Query& rhs) {
        
        if (l / sqrtN == rhs.l / sqrtN) return r < rhs.r;
        return l / sqrtN < rhs.l / sqrtN;
    }
};

std::array<int, N_MAX> hat;
std::array<Query, M_MAX> queries;
std::array<int, C_MAX> cnt;
std::array<int, M_MAX> res;
std::bitset<C_MAX> exceptional;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> C;
    
    for (int input, idx = 0; idx < N; ++idx) {
        
        std::cin >> input;
        hat[idx] = input - 1;
    }
    
    std::cin >> M;
    
    for (int A, B, idx = 0; idx < M; ++idx) {
        
        std::cin >> A >> B;
        queries[idx].idx = idx;
        queries[idx].l = A - 1;
        queries[idx].r = B - 1;
    }
}

void solve() {
    
    sqrtN = sqrt(N);
    
    std::sort(queries.begin(), queries.begin() + M);
    
    for (int prev = -1, intervalL, intervalR, l, r, maxCnt, maxColor, realMaxCnt, realMaxColor, idx = 0; idx < M; ++idx) {
        
        if (queries[idx].l / sqrtN != prev) {
            
            prev = queries[idx].l / sqrtN;
            maxCnt = 0;
            std::fill(cnt.begin(), cnt.begin() + C, 0);
            exceptional.reset();
            
            intervalL = prev * sqrtN;
            intervalR = std::min((prev + 1) * sqrtN, N);
            
            for (int cursor = intervalL; cursor < intervalR; ++cursor) {
                
                exceptional[hat[cursor]] = true;
            }
            
            l = queries[idx].l;
            r = queries[idx].r;
            
            for (int cursor = l; cursor <= r; ++cursor) {
                
                ++cnt[hat[cursor]];
                
                if (!exceptional[hat[cursor]] && cnt[hat[cursor]] > maxCnt) {
                    
                    maxCnt = cnt[hat[cursor]];
                    maxColor = hat[cursor];
                }
            }
        }
        else {
            
            while (l < queries[idx].l) cnt[hat[l++]]--;
            
            while (l > queries[idx].l) cnt[hat[--l]]++;
            
            while (r < queries[idx].r) {
                
                cnt[hat[++r]]++;
                
                if (!exceptional[hat[r]] && cnt[hat[r]] > maxCnt) {
                    
                    maxCnt = cnt[hat[r]];
                    maxColor = hat[r];
                }
            }
        }
        
        realMaxCnt = maxCnt;
        realMaxColor = maxColor;
        
        for (int cursor = intervalL; cursor < intervalR; ++cursor) {
            
            if (cnt[hat[cursor]] > realMaxCnt) {
                
                realMaxCnt = cnt[hat[cursor]];
                realMaxColor = hat[cursor];
            }
        }
        
        res[queries[idx].idx] = (realMaxCnt > (r - l + 1) / 2) ? (realMaxColor + 1) : 0;
    }
    
    for (int idx = 0; idx < M; ++idx) {
        
        if (res[idx]) std::cout << "yes " << res[idx] << '\n';
        else std::cout << "no\n";
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

