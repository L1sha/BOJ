#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N, M;
std::array<std::pair<int, int>, N_MAX> input;
std::array<int, N_MAX> compressedInput, realValue;
std::array<std::vector<int>, 4 * N_MAX> segTree;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) {
        
        segTree[cursor] = {compressedInput[l]};
    }
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        const auto& left = segTree[cursor * 2];
        const auto& right = segTree[cursor * 2 + 1];
        
        segTree[cursor].resize(left.size() + right.size());
        
        std::merge(left.begin(), left.end(), right.begin(), right.end(),
            segTree[cursor].begin());
    }
}

int segQuery(const int& ql, const int& qr, const int& num,
    int cursor = 1, int l = 1, int r = N) {
    
    if (l > qr || r < ql) return 0;
    else if (l >= ql && r <= qr) {
        
        return std::distance(segTree[cursor].begin(),
            std::upper_bound(segTree[cursor].begin(), segTree[cursor].end(), num));
    }
    else {
        
        return segQuery(ql, qr, num, cursor * 2, l, l + (r - l) / 2)
            + segQuery(ql, qr, num, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

int binarySearch(const int& I, const int& J, const int& K) {
    
    int l = 0, r = N, mid;
    
    while (r - l > 1) {
        
        mid = (l + r) / 2;
        
        if (segQuery(I, J, mid) < K) l = mid;
        else r = mid;
    }
    
    return realValue[r];
}

void get_input() {
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> input[idx].first;
        input[idx].second = idx;
    }
    
    std::sort(input.begin() + 1, input.begin() + N + 1);
    
    for (int idx = 1, prev = -1, cnt = 0; idx <= N; ++idx) {
        
        realValue[idx] = input[idx].first;
        
        if (prev == realValue[idx]) ++cnt;
        else {
            
            prev = realValue[idx];
            cnt = 0;
        }
        
        compressedInput[input[idx].second] = idx - cnt;
    }
}

void solve() {
    
    segInit();
    
    for (int I, J, K; M--; ) {
        
        std::cin >> I >> J >> K;
        
        std::cout << binarySearch(I, J, K) << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}