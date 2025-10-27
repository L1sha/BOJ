#include "bits/stdc++.h"


int N, M, ql, qr;
std::array<int, 100'001> num;
std::array<int, 400'004> seg;

int init(int idx, int l, int r){
    
    if (l == r) return seg[idx] = num[l];
    else return seg[idx] = init(idx * 2, l, l + (r - l) / 2) + init(idx * 2 + 1, l + (r - l) / 2 + 1, r);
}

int query(int idx, int l, int r){
    
    if (r < ql || l > qr) return 0;
    else if (r <= qr && l >= ql) return seg[idx];
    else return query(idx * 2, l, l + (r - l) / 2) + query(idx * 2 + 1, l + (r - l) / 2 + 1, r);
}





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> num[idx];
    init(1, 1, N);
    
    while (M--) {
        
        std::cin >> ql >> qr;
        std::cout << query(1, 1, N) << '\n';
    }
    
    return 0;
}


