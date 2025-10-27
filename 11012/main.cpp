#include "bits/stdc++.h"


constexpr int N_MAX = 10'000, MIN = -1, MAX = 1e5 + 1;

int T, N, M, L, R, b, t, res;

std::array<std::pair<int, int>, N_MAX> pts;
std::array<std::vector<int>, 4 * N_MAX> segTree;

const std::vector<int>& segInit(int cursor = 1, int l = 0, int r = N - 1) {
    
    if (l == r) {
        
        return segTree[cursor] = {pts[l].second};
    }
    
    const std::vector<int>& left = segInit(cursor * 2, l, l + (r - l) / 2);
    const std::vector<int>& right = segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    
    segTree[cursor].resize(left.size() + right.size());
    std::merge(left.begin(), left.end(), right.begin(), right.end(), segTree[cursor].begin());
    
    return segTree[cursor];
} 

void init() {
    
    std::sort(pts.begin(), pts.begin() + N);
    
    segInit();
}

int countNumbersInRange(const std::vector<int>& V) {
    
    return std::distance(std::lower_bound(V.begin(), V.end(), b), std::upper_bound(V.begin(), V.end(), t));
}

int segQuery(int cursor = 1, int l = 0, int r = N - 1) {
    
    if (l > R || r < L) {
        
        return 0;
    }
    
    if (l >= L && r <= R) {
        
        return countNumbersInRange(segTree[cursor]);
    }
    
    return segQuery(cursor * 2, l, l + (r - l) / 2) + segQuery(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

int query() {
    
    L = std::distance(pts.begin(), std::lower_bound(pts.begin(), pts.begin() + N, std::make_pair(L, MIN)));
    R = std::distance(pts.begin(), std::lower_bound(pts.begin(), pts.begin() + N, std::make_pair(R, MAX))) - 1;
    
    if (L > R) return 0;
    
    return segQuery();
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        res = 0;
        
        std::cin >> N >> M;
        
        for (int idx = 0; idx < N; ++idx) {
            
            std::cin >> pts[idx].first >> pts[idx].second;
        }
        
        init();
        
        while (M--) {
            
            std::cin >> L >> R >> b >> t;
            
            res += query();
        }
        
        std::cout << res << '\n';
    }
    
    return 0;
}

