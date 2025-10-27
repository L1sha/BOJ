#include "bits/stdc++.h"

int N;

std::vector<std::pair<long long, long long>> segTree;
std::vector<long long> lazy;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

long long GCD(const long long& a, const long long& b) {
    
    if (b == 0) return a;
    if (a == 0) return b;
    return std::gcd(a, b);
}

std::pair<long long, long long> merge(const std::pair<long long, long long>& left, const std::pair<long long, long long>& right) {
    
    std::pair<long long, long long> res;
    
    res.first = std::min(left.first, right.first);
    res.second = GCD(std::max(left.first, right.first) - res.first, GCD(left.second, right.second));
    
    return res;
}

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) std::cin >> segTree[cursor].first;
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = merge(segTree[cursor * 2], segTree[cursor * 2 + 1]);
    }
}

void get_input() {
    
    std::cin >> N;
    
    segTree.resize(4 * N);
    lazy.resize(4 * N);
    segInit();
}

void lazyUpdate(const int& cursor, const int& l, const int& r) {
    
    if (lazy[cursor]) {
        
        segTree[cursor].first += lazy[cursor];
        
        if (l != r) {
            
            lazy[cursor * 2] += lazy[cursor];
            lazy[cursor * 2 + 1] += lazy[cursor];
        }
        
        lazy[cursor] = 0;
    }
}

void segUpdate(const int& ql, const int& qr, const long long& val, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (l > qr || r < ql) return;
    else if (l >= ql && r <= qr) {
        
        segTree[cursor].first += val;
        
        if (l != r) {
            
            lazy[cursor * 2] += val;
            lazy[cursor * 2 + 1] += val;
        }
    }
    else {
        
        segUpdate(ql, qr, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate(ql, qr, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = merge(segTree[cursor * 2], segTree[cursor * 2 + 1]);
    }
}

std::pair<long long, long long> segQuery(const int& ql, const int& qr, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (l > qr || r < ql) return {0, 0};
    else if (l >= ql && r <= qr) return segTree[cursor];
    else {
        
        return merge(segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2),
            segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r));
    }
}

void Query(const int& ql, const int& qr) {
    
    auto [first, second] = segQuery(ql, qr);
    std::cout << GCD(first, second) << '\n';
}
 
void solve() {
    
    int Q, T, A, B;
    std::cin >> Q;
    
    while (Q--) {
        
        std::cin >> T >> A >> B;
        
        if (T) {
            
            segUpdate(A, B, T);
        }
        else {
            
            Query(A, B);
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

