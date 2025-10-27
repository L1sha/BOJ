#include "bits/stdc++.h"


int N, M, ql, qr, k;
std::array<int, 100'001> A;
std::array<long long, 400'004> segTree;

void init(int cursor, int l, int r) {
    
    if (l == r) {
        
        segTree[cursor] = A[l];
        return;
    }
    
    init(cursor * 2, l, l + (r - l) / 2);
    init(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

void insert(int cursor, int l, int r) {
    
    if (qr < l || ql > r) {
        
        return;
    }
    
    if (ql <= l && r <= qr) {
        
        segTree[cursor] += k;
        return;
    }
    
    insert(cursor * 2, l, l + (r - l) / 2);
    insert(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

long long query(int cursor, int l, int r) {
    
    if (k < l || k > r) {
        
        return 0;
    }
    
    if (l == r) {
        
        return segTree[cursor];
    }
    
    return segTree[cursor] + query(cursor * 2, l, l + (r - l) / 2) + query(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> A[idx];
    }
    
    init(1, 1, N);
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> k;
        
        switch (k) {
            
            case 1:
            
            std::cin >> ql >> qr >> k;
            insert(1, 1, N);
            
            break;
            
            case 2:
            
            std::cin >> k;
            std::cout << query(1, 1, N) << '\n';
            
            break;
        }
    }
    
    return 0;
}

