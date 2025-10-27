#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

constexpr int N_MAX = 75'000;

int T, N;
std::array<intPair, N_MAX> islands;
std::array<intPair, 4 * N_MAX> segTree;

intPair segInit(int cursor, int l, int r) {
    
    if (l == r) {
        
        return segTree[cursor] = {islands[l].second, 1};
    }
    
    auto left = segInit(cursor * 2, l, l + (r - l) / 2);
    auto right = segInit(cursor * 2 + 1, l + (r - l) / 2 + 1,  r);
    
    return segTree[cursor] = {std::min(left.first, right.first), left.second + right.second};
}

intPair segFind(int cursor, int l, int r, const int& target, int& ans) {
    
    if (l == r) {
        
        ans = l;
        
        return segTree[cursor] = {2e9, 0};
    }
    
    if (segTree[cursor * 2].first == target) {
        
        auto left = segFind(cursor * 2, l, l + (r - l) / 2, target, ans);
        const auto& right = segTree[cursor * 2 + 1];
        
        return segTree[cursor] = {std::min(left.first, right.first), left.second + right.second};
    }
    else {
        
        const auto& left = segTree[cursor * 2];
        auto right = segFind(cursor * 2 + 1, l + (r - l) / 2 + 1, r, target, ans);
        
        return segTree[cursor] = {std::min(left.first, right.first), left.second + right.second};
    }
}

int segCount(int cursor, int l, int r, const int& ql, const int& qr) {
    
    if (r < ql || l > qr) {
        
        return 0;
    }
    
    if (r <= qr && l >= ql) {
        
        return segTree[cursor].second;
    }
    
    return segCount(cursor * 2, l, l + (r - l) / 2, ql, qr) + segCount(cursor * 2 + 1, l + (r - l) / 2 + 1, r, ql, qr);
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> N;
        
        for (int idx = 0; idx < N; ++idx) {
            
            std::cin >> islands[idx].first >> islands[idx].second;
            islands[idx].first *= -1;
        }
        
        std::sort(islands.begin(), islands.begin() + N);
        
        segInit(1, 0, N - 1);
        
        long long res = 0;
        int target, ans, ql, qr = N - 1;
        
        for (int idx = 0; idx < N; ++idx) {
            
            target = segTree[1].first;
            segFind(1, 0, N - 1, target, ans);
            
            if (ans != N - 1) {
                
                ql = ans + 1;
                res += segCount(1, 0, N - 1, ql, qr);
            }
        }
        
        std::cout << res << '\n';
    }
    
    return 0;
}

