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
    
    std::cin >> N;
    
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
    
    if (lazy[cursor] == 1) {
        
        segTree[cursor] = r - l + 1;
        
        if (l != r) {
            
            lazy[cursor * 2] = 1;
            lazy[cursor * 2 + 1] = 1;
        }
    }
    else if (lazy[cursor] == 2) {
        
        segTree[cursor] = 0;
        
        if (l != r) {
            
            lazy[cursor * 2] = 2;
            lazy[cursor * 2 + 1] = 2;
        }
    }
    
    lazy[cursor] = 0;
}

void segUpdate(const int& ql, const int& qr, const int& val, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (r < ql || l > qr) return;
    else if (r <= qr && l >= ql) {
        
        if (val == 1) segTree[cursor] = r - l + 1;
        else segTree[cursor] = 0;
        
        if (l != r) {
            
            lazy[cursor * 2] = val;
            lazy[cursor * 2 + 1] = val;
        }
    }
    else {
        
        segUpdate(ql, qr, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate(ql, qr, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = segTree[cursor * 2] + segTree[cursor * 2 + 1];
    }
}

void update(const int& target, const int& val) {
    
    if (interval[target].first == interval[target].second) return;
    
    segUpdate(interval[target].first + 1, interval[target].second, val);
}

int segQuery(const int& ql, const int& qr, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (r < ql || l > qr) return 0;
    if (r <= qr && l >= ql) return segTree[cursor];
    else return segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2) + segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

int query(const int& target) {
    
    if (interval[target].first == interval[target].second) return 0;
    
    return segQuery(interval[target].first + 1, interval[target].second);
}

void solve() {
    
    DFS();
    
    update(1, 1);
    
    std::cin >> M;
    
    for (int q, i; M--; ) {
        
        std::cin >> q >> i;
        
        switch (q) {
            
            case 1:
            
            update(i, 1);
            
            break;
            
            case 2:
            
            update(i, 2);
            
            break;
            
            case 3:
            
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

