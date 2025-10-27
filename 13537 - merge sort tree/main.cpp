#include "bits/stdc++.h"


constexpr int N_MAX = 100'000;

int N, M, I, J, K;

std::array<int, N_MAX + 1> A;
std::array<std::vector<int>, 4 * N_MAX + 1> segTree;

const std::vector<int>& init(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) {
        
        return segTree[cursor] = {A[l]};
    }
    
    const auto& left = init(cursor * 2, l, l + (r - l) / 2);
    const auto& right = init(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    
    segTree[cursor].resize(left.size() + right.size());
    std::merge(left.begin(), left.end(), right.begin(), right.end(), segTree[cursor].begin());
    
    return segTree[cursor];
}

int query(int cursor = 1, int l = 1, int r = N) {
    
    if (l > J || r < I) {
        
        return 0;
    }
    
    if (l >= I && r <= J) {
        
        return std::distance(std::upper_bound(segTree[cursor].begin(), segTree[cursor].end(), K), segTree[cursor].end());
    }
    
    return query(cursor * 2, l, l + (r - l) / 2) + query(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> A[idx];
    }
    
    init();
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> I >> J >> K;
        
        std::cout << query() << '\n';
    }
    
    return 0;
}

