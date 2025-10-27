#include "bits/stdc++.h"

constexpr int N_MAX = 100'000, M_MAX = 100'000;

int N, sqrtN, M;

struct Query {
    
    int ql, qr, qidx;
    
    bool operator<(const Query& rhs) {
        
        if (ql / sqrtN == rhs.ql / sqrtN) return qr < rhs.qr;
        return ql / sqrtN < rhs.ql / sqrtN;
    }
};

std::array<int, N_MAX + 1> A;
std::array<std::pair<int, int>, N_MAX * 2 + 1> right, temp;
std::array<Query, M_MAX> queries;
std::array<int, M_MAX> finalRes;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int idx = 1; idx <= N; ++idx) std::cin >> A[idx];
    
    std::cin >> M;
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> queries[idx].ql >> queries[idx].qr;
        queries[idx].qidx = idx;
    }
}

int manually(const int& ql, const int& qr) {
    
    int partialSum = 0, res = 0, min = 0, max = 0;
    
    temp[N_MAX].first = ql - 1;
    
    for (int idx = ql; idx <= qr; ++idx) {
        
        partialSum += A[idx];
        min = std::min(min, partialSum);
        max = std::max(max, partialSum);
        
        if (temp[N_MAX + partialSum].first == -1) temp[N_MAX + partialSum].first = idx;
        temp[N_MAX + partialSum].second = idx;
        
        res = std::max(res, idx - temp[N_MAX + partialSum].first);
    }
    
    for (int idx = N_MAX + min; idx <= N_MAX + max; ++idx) temp[idx] = {-1, -1};
    
    return res;
}

void solve() {
    
    sqrtN = static_cast<int>(ceil(sqrt(N)));
    
    std::sort(queries.begin(), queries.begin() + M);
    
    int prev = -1, l = 0, r = 0, leftSum = 0, rightSum = 0, min = 0, max = 0, res = 0;
    
    std::fill(right.begin(), right.end(), std::make_pair(-1, -1));
    std::fill(temp.begin(), temp.end(), std::make_pair(-1, -1));
    
    for (int idx = 0; idx < M; ++idx) {
        
        const auto [ql, qr, qidx] = queries[idx];
        
        if (ql / sqrtN != prev) {
            
            prev = ql / sqrtN;
            
            r = (prev + 1) * sqrtN;
            rightSum = 0;
            
            for (int idx = N_MAX + min; idx <= N_MAX + max; ++idx) right[idx] = {-1, -1};
            right[N_MAX].first = r - 1;
            
            min = 0;
            max = 0;
            res = 0;
        }
        
        if (qr < (prev + 1) * sqrtN) {
            
            finalRes[qidx] = manually(ql, qr);
        }
        else {
            
            while (r <= qr) {
                
                rightSum += A[r];
                min = std::min(min, rightSum);
                max = std::max(max, rightSum);
                
                if (right[N_MAX + rightSum].first == -1) right[N_MAX + rightSum].first = r;
                right[N_MAX + rightSum].second = r;
                
                res = std::max(res, r - right[N_MAX + rightSum].first);
                
                ++r;
            }
            
            leftSum = 0;
            finalRes[qidx] = res;
            
            for (l = (prev + 1) * sqrtN - 1; l >= ql; --l) {
                
                leftSum += A[l];
                
                if (right[N_MAX - leftSum].second) finalRes[qidx] = std::max(finalRes[qidx], right[N_MAX - leftSum].second - l + 1);
            }
            
            finalRes[qidx] = std::max(finalRes[qidx], manually(ql, (prev + 1) * sqrtN - 1));
        }
    }
    
    for (int idx = 0; idx < M; ++idx) std::cout << finalRes[idx] << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

