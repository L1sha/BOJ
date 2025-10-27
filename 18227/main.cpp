#include "bits/stdc++.h"


constexpr int N_MAX = 200'001;

int N, C, X, Y, Q, qType, A, cnt, height;

std::array<std::vector<int>, N_MAX> adjL;
std::array<int, N_MAX> left, right, rank;
std::array<int, N_MAX * 4> segTree;

void DFS(int cursor = C, int parent = 0) {
    
    left[cursor] = ++cnt;
    rank[cursor] = ++height;
    
    for (const int& next : adjL[cursor]) {
        
        if (next != parent) {
            
            DFS(next, cursor);
        }
    }
    
    right[cursor] = cnt;
    height--;
}

void segUpdate(int cursor = 1, int l = 1, int r = N) {
    
    if (r < left[A] || l > left[A]) return;
    
    if (r == l) {
        
        segTree[cursor]++;
        return;
    }
    
    segUpdate(cursor * 2, l, l + (r - l) / 2);
    segUpdate(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    
    segTree[cursor] = segTree[cursor * 2] + segTree[cursor * 2 + 1];
}

int segQuery(int cursor = 1, int l = 1, int r = N) {
    
    if (r < left[A] || l > right[A]) return 0;
    
    if (r <= right[A] && l >= left[A]) return segTree[cursor];
    
    return segQuery(cursor * 2, l, l + (r - l) / 2) + segQuery(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

long long query() {
    
    return segQuery() * (long long) rank[A];
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> C;
    
    for (int idx = 1; idx < N; ++idx) {
        
        std::cin >> X >> Y;
        adjL[X].push_back(Y);
        adjL[Y].push_back(X);
    }
    
    DFS();
    
    std::cin >> Q;
    
    while (Q--) {
        
        std::cin >> qType >> A;
        
        switch (qType) {
            
            case 1:
            
            segUpdate();
            
            break;
            
            case 2:
            
            std::cout << query() << '\n';
            
            break;
        }
    }
    
    return 0;
}

