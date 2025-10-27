#include "bits/stdc++.h"


int T, N, M, num, target, ql = 1, qr;
std::array<int, 800'000> segTree;
std::unordered_map<int, int> map;

int init(int idx, int l, int r) {
    
    if (l == r) {
        
        if (l > M) {
            
            return segTree[idx] = 1;
        }
        else {
        
            return segTree[idx] = 0;
        }
    }
    
    return segTree[idx] = init(idx * 2, l, l + (r - l) / 2) + init(idx * 2 + 1, l + (r - l) / 2 + 1, r);
}

int update(int idx, int l, int r) {
    
    if (l > target || r < target) {
        
        return segTree[idx];
    }
    
    if (l == r) {
        
        return segTree[idx] = (segTree[idx] + 1) % 2;
    }
    
    return segTree[idx] = update(idx * 2, l, l + (r - l) / 2) + update(idx * 2 + 1, l + (r - l) / 2 + 1, r);
}

int query(int idx, int l, int r) {
    
    if (l > qr || r < ql) {
        
        return 0;
    }
    
    if (l >= ql && r <= qr) {
        
        return segTree[idx];
    }
    
    return query(idx * 2, l, l + (r - l) / 2) + query(idx * 2 + 1, l + (r - l) / 2 + 1, r);
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> N >> M;
        
        init(1, 1, N + M);
        
        for (int idx = 1; idx <= N; ++idx) {
            
            map[idx] = M + idx;
        }
        
        for (int cursor = M; cursor; --cursor) {
            
            std::cin >> num;
            
            target = map[num];
            update(1, 1, N + M);
            
            qr = map[num];
            std::cout << query(1, 1, N + M) << ' ';
            
            map[num] = cursor;
            target = cursor;
            update(1, 1, N + M);
        }
        
        std::cout << '\n';
    }
    
    return 0;
}

