#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N, M;

std::array<std::vector<int>, N_MAX> children;
std::array<std::pair<int, int>, N_MAX> interval;
std::array<int, N_MAX * 4> segTree, lazy;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    int input;
    std::cin >> input;
    
    for (int idx = 2; idx <= N; ++idx) {
        
        std::cin >> input;
        
        children[input].push_back(idx);
    }
}

void DFS(int cursor = 1) {
    
    static int cnt = 0;
    
    interval[cursor].first = ++cnt;
    
    for (const int& child : children[cursor]) DFS(child);
    
    interval[cursor].second = cnt;
}

void lazyUpdate(const int& cursor, const int& l, const int& r) {
    
    if (l != r) {
        
        lazy[cursor * 2] += lazy[cursor];
        lazy[cursor * 2 + 1] += lazy[cursor];
    }
    else {
        
        segTree[cursor] += lazy[cursor];
    }
    
    lazy[cursor] = 0;
}

void segUpdate(const int& ql, const int& qr, const int& val, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (r < ql || l > qr) return;
    else if (r <= qr && l >= ql) {
        
        if (l != r) {
            
            lazy[cursor * 2] += val;
            lazy[cursor * 2 + 1] += val;
        }
        else {
            
            segTree[cursor] += val;
        }
    }
    else {
        
        segUpdate(ql, qr, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate(ql, qr, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void update(const int& target, const int& val) {
    
    segUpdate(interval[target].first, interval[target].second, val);
}

int segQuery(const int& target, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (r < target || l > target) return 0;
    if (l == r) return segTree[cursor];
    else return segQuery(target, cursor * 2, l, l + (r - l) / 2) + segQuery(target, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

int query(const int& target) {
    
    return segQuery(interval[target].first);
}

void solve() {
    
    DFS();
    
    for (int q, i, w; M--; ) {
        
        std::cin >> q;
        
        switch (q) {
            
            case 1:
            
            std::cin >> i >> w;
            update(i, w);
            
            break;
            
            case 2:
            
            std::cin >> i;
            std::cout << query(i) << '\n';
            
            break;
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

