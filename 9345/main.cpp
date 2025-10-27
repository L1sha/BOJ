#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int T, N, K, Q, A, B;
std::array<intPair, 400'004> segTree;
std::array<int, 100'001> DVD;

void initSegTree(int cursor, int l, int r) {
    
    segTree[cursor] = {l, r};
    
    if (l != r) {
        
        initSegTree(cursor * 2, l, l + (r - l) / 2);
        initSegTree(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void init() {
    
    for (int idx = 0; idx < N; ++idx) {
        
        DVD[idx] = idx;
    }
    
    initSegTree(1, 0, N - 1);
}

std::pair<int, int> update(int cursor, int l, int r, const int& target, const int& value) {
    
    if (target < l || target > r) {
        
        return segTree[cursor];
    }
    
    if (l == r) {
        
        return segTree[cursor] = {value, value};
    }
    
    auto left = update(cursor * 2, l, l + (r - l) / 2, target, value);
    auto right = update(cursor * 2 + 1, l + (r - l) / 2 + 1, r, target, value);
    
    return segTree[cursor] = {std::min(left.first, right.first), std::max(left.second, right.second)};
}

void changeDVD() {
    
    std::swap(DVD[A], DVD[B]);
    
    update(1, 0, N - 1, A, DVD[A]);
    update(1, 0, N - 1, B, DVD[B]);
}

std::pair<int, int> query(int cursor, int l, int r, const int& ql, const int& qr) {
    
    if (l > qr || r < ql) {
        
        return {N, -1};
    }
    
    if (l >= ql && r <= qr) {
        
        return segTree[cursor];
    }
    
    auto left = query(cursor * 2, l, l + (r - l) / 2, ql, qr);
    auto right = query(cursor * 2 + 1, l + (r - l) / 2 + 1, r, ql, qr);
    
    return {std::min(left.first, right.first), std::max(left.second, right.second)};
}

void check() {
    
    auto res = query(1, 0, N - 1, A, B);
    
    if (res.first == A && res.second == B) {
        
        std::cout << "YES\n";
    }
    else {
        
        std::cout << "NO\n";
    }
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> N >> K;
        
        init();
        
        while (K--) {
            
            std::cin >> Q >> A >> B;
            
            switch (Q) {
                
                case 0:
                
                changeDVD();
                break;
                
                case 1:
                
                check();
                break;
            }
        }
    }
    
    return 0;
}

