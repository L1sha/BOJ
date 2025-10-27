#include "bits/stdc++.h"


constexpr int N_MAX = 100'001;

int N, M, cnt, parent, Q, I, W;
std::array<std::vector<int>, N_MAX> children;
std::array<int, N_MAX> left, right;
std::array<int, 4 * N_MAX> segTree, lazy;

void DFS(int cursor = 1) {
    
    left[cursor] = ++cnt;
    
    for (const int& next : children[cursor]) DFS(next);
    
    right[cursor] = cnt;
}

void lazyUpdate(const int& cursor, const int& l, const int& r) {
    
    if (lazy[cursor]) {
        
        if (l != r) {
            
            lazy[cursor * 2] += lazy[cursor];
            lazy[cursor * 2 + 1] += lazy[cursor];
        }
        
        segTree[cursor] += (r - l + 1) * lazy[cursor];
        lazy[cursor] = 0;
    }
}

void segUpdate(int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (l > right[I] || r < left[I]) return;
    
    if (l >= left[I] && r <= right[I]) {
        
        segTree[cursor] += (r - l + 1) * W;
        
        if (l != r) {
            
            lazy[cursor * 2] += W;
            lazy[cursor * 2 + 1] += W;
        }
        
        return;
    }
    
    segUpdate(cursor * 2, l, l + (r - l) / 2);
    segUpdate(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

int segQuery(int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (l > left[I] || r < left[I]) return 0;
    
    if (l == r) {
        
        return segTree[cursor];
    }
    
    return segQuery(cursor * 2, l, l + (r - l) / 2) + segQuery(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> parent;
    
    for (int idx = 2; idx <= N; ++idx) {
        
        std::cin >> parent;
        children[parent].push_back(idx);
    }
    
    DFS();
    
    while (M--) {
        
        std::cin >> Q;
        
        switch (Q) {
            
            case 1 :
            
            std::cin >> I >> W;
            segUpdate();
            
            break;
            
            case 2 :
            
            std::cin >> I;
            std::cout << segQuery() << '\n';
            
            break;
        }
    }
    
    return 0;
}

