#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N, M, LAST_ANS, a, b, c, i, j, k;

std::array<int, N_MAX> A;
std::array<std::vector<int>, N_MAX * 4> segTree;

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) {
        
        segTree[cursor] = {A[l]};
    }
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        const auto& left = segTree[cursor * 2];
        const auto& right = segTree[cursor * 2 + 1];
        
        segTree[cursor].resize(left.size() + right.size());
        std::merge(left.begin(), left.end(), right.begin(), right.end(), segTree[cursor].begin());
    }
}

int segQuery(int cursor = 1, int l = 1, int r = N) {
    
    if (r < i || l > j) return 0;
    
    if (r <= j && l >= i) return std::distance(std::upper_bound(segTree[cursor].begin(), segTree[cursor].end(), k), segTree[cursor].end());
    
    return segQuery(cursor * 2, l, l + (r - l) / 2) + segQuery(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}



int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> A[idx];
    
    segInit();
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> a >> b >> c;
        i = a ^ LAST_ANS;
        j = b ^ LAST_ANS;
        k = c ^ LAST_ANS;
        
        LAST_ANS = segQuery();
        std::cout << LAST_ANS << '\n';
    }

    return 0;
}
