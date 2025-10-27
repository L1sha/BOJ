#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N, M;
bool sw;

std::array<std::vector<int>, N_MAX> children;
std::array<std::pair<int, int>, N_MAX> interval;
std::array<int, N_MAX * 4> segTree1, lazy, segTree2;



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
        
        segTree1[cursor] += lazy[cursor];
    }
    
    lazy[cursor] = 0;
}

void segUpdate1(const int& ql, const int& qr, const int& val, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (r < ql || l > qr) return;
    else if (r <= qr && l >= ql) {
        
        if (l != r) {
            
            lazy[cursor * 2] += val;
            lazy[cursor * 2 + 1] += val;
        }
        else {
            
            segTree1[cursor] += val;
        }
    }
    else {
        
        segUpdate1(ql, qr, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate1(ql, qr, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

int segQuery1(const int& target, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (r < target || l > target) return 0;
    if (l == r) return segTree1[cursor];
    else return segQuery1(target, cursor * 2, l, l + (r - l) / 2) + segQuery1(target, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

void segUpdate2(const int& target, const int& val, int cursor = 1, int l = 1, int r = N) {
    
    if (r < target || l > target) return;
    else if (l == r) segTree2[cursor] += val;
    else {
        
        segUpdate2(target, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate2(target, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree2[cursor] = segTree2[cursor * 2] + segTree2[cursor * 2 + 1];
    }
}

int segQuery2(const int& ql, const int& qr, int cursor = 1, int l = 1, int r = N) {
    
    if (r < ql || l > qr) return 0;
    if (r <= qr && l >= ql) return segTree2[cursor];
    else return segQuery2(ql, qr, cursor * 2, l, l + (r - l) / 2) + segQuery2(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

void update(const int& target, const int& val) {
    
    if (!sw) segUpdate1(interval[target].first, interval[target].second, val);
    else segUpdate2(interval[target].first, val);
}

int query(const int& target) {
    
    return segQuery1(interval[target].first) + segQuery2(interval[target].first, interval[target].second);
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
            
            case 3:
            
            sw = !sw;
            
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