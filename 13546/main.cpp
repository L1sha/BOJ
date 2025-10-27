#include "bits/stdc++.h"

constexpr int N_MAX = 100'001, K_MAX = 100'001, M_MAX = 100'000;

int N, K, M, sqrtN;

struct Query {
    
    int ql, qr, qidx;
    
    bool operator<(const Query& rhs) {
        
        if (ql / sqrtN == rhs.ql / sqrtN) return qr < rhs.qr;
        return ql / sqrtN < rhs.ql / sqrtN;
    }
};

std::array<int, N_MAX> A;
std::array<int, K_MAX> leftmost, rightmost;
std::array<Query, M_MAX> queries;
std::array<int, M_MAX> resSave;




void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K;
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> A[idx];
    
    std::cin >> M;
    
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> queries[idx].ql >> queries[idx].qr;
        queries[idx].qidx = idx;
    }
}

int manually(const int& ql, const int& qr) {
    
    int res = 0;
    
    std::map<int, int> temp;
    
    temp.emplace(A[ql], ql);
    
    for (int idx = ql + 1; idx <= qr; ++idx) {
        
        if (temp.count(A[idx])) res = std::max(res, idx - temp[A[idx]]);
        else temp.emplace(A[idx], idx);
    }
    
    return res;
}

void solve() {
    
    sqrtN = static_cast<int>(ceil(sqrt(N)));
    
    std::sort(queries.begin(), queries.begin() + M);
    
    int prev = -1, l, r, res;
    
    for (int idx = 0; idx < M; ++idx) {
        
        const auto [ql, qr, qidx] = queries[idx];
        
        if (prev != ql / sqrtN) {
            
            prev = ql / sqrtN;
            r = (prev + 1) * sqrtN;
            res = 0;
            
            for (int num = 1; num <= K; ++num) {
                
                leftmost[num] = 0;
                rightmost[num] = 0;
            }
        }
        
        if (qr < (prev + 1) * sqrtN) {
            
            resSave[qidx] = manually(ql, qr);
        }
        else {
            
            while (r <= qr) {
                
                rightmost[A[r]] = r;
                
                if (leftmost[A[r]] == 0) {
                    
                    leftmost[A[r]] = r;
                }
                else {
                    
                    res = std::max(res, r - leftmost[A[r]]);
                }
                
                ++r;
            }
            
            resSave[qidx] = std::max(res, manually(ql, (prev + 1) * sqrtN - 1));
            
            for (l = (prev + 1) * sqrtN - 1; l >= ql; --l) {
                
                if (rightmost[A[l]]) {
                    
                    resSave[qidx] = std::max(resSave[qidx], rightmost[A[l]] - l);
                }
            }
        }
    }
    
    for (int idx = 0; idx < M; ++idx) std::cout << resSave[idx] << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

