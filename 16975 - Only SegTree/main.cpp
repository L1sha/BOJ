#include "bits/stdc++.h"


int N, M, ql, qr, k, target;
std::array<int, 100'001> A;
std::array<long long, 400'004> segTree;

long long init(int cursor, int l, int r) {
    
    if (l == r) {
        
        return segTree[cursor] = A[l] - A[l - 1];
    }
    
    return segTree[cursor] = init(cursor * 2, l, l + (r - l) / 2) + init(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

long long update(int cursor, int l, int r) {
    
    if (target < l || target > r) {
        
        return segTree[cursor];
    }
    
    if (l == r) {
        
        return segTree[cursor] += k;
    }
    
    return segTree[cursor] = update(cursor * 2, l, l + (r - l) / 2) + update(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

long long query(int cursor, int l, int r) {
    
    if (qr < l) {
        
        return 0;
    }
    
    if (r <= qr) {
        
        return segTree[cursor];
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
    
    init(1, 1, N);
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> k;
        
        switch (k) {
            
            case 1:
            
            std::cin >> target >> qr >> k;
            update(1, 1, N);
            
            if (qr != N) {
                
                k = -k;
                target = qr + 1;
                update(1, 1, N);
            }
            
            break;
            
            case 2:
            
            std::cin >> qr;
            std::cout << query(1, 1, N) << '\n';
            
            break;
        }
    }
    
    return 0;
}

