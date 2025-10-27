#include "bits/stdc++.h"

constexpr int N_MAX = 500'000;

using intPair = std::pair<int, int>;

struct Score {
    
    int first, second, third;
    
    bool operator< (const Score& rhs) {
        
        return first < rhs.first;
    }
};

int N;

std::array<Score, N_MAX> scores;
std::array<int, N_MAX * 4> segTree;

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    int temp;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> temp;
        scores[temp - 1].first = idx;
    }
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> temp;
        scores[temp - 1].second = idx;
    }
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> temp;
        scores[temp - 1].third = idx;
    }
}

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    segTree[cursor] = N + 1;
    
    if (l != r) {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void segUpdate(const int& target, const int& val, int cursor = 1, int l = 1, int r = N) {
    
    if (l > target || r < target) return;
    else if (l == r) segTree[cursor] = val;
    else {
        
        segUpdate(target, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate(target, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = std::min(segTree[cursor * 2], segTree[cursor * 2 + 1]);
    }
}

int segQuery(const int& ql, const int& qr, int cursor = 1, int l = 1, int r = N) {
    
    if (l > qr || r < ql) return N + 1;
    else if (l >= ql && r <= qr) return segTree[cursor];
    else {
        
        return std::min(segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2),
            segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r));
    }
}

void solve() {
    
    std::sort(scores.begin(), scores.begin() + N);
    
    segInit();
    
    int res = 0;
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (segQuery(1, scores[idx].second) > scores[idx].third) ++res;
        
        segUpdate(scores[idx].second, scores[idx].third);
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

