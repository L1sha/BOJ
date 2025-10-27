#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;
const int INF = 1e9;

int N;

struct Node {
    
    int left, mid, right, sum;
};

    
Node merge(const Node& l, const Node& r) {
    
    Node res;
    
    res.left = std::max(l.left, l.sum + r.left);
    res.mid = std::max(std::max(l.mid, r.mid), l.right + r.left);
    res.right = std::max(r.right, r.sum + l.right);
    res.sum = l.sum + r.sum;
    
    return res;
}

std::array<int, N_MAX> A;
std::array<Node, N_MAX * 4> segTree;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> A[idx];
    }
}

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) segTree[cursor] = {A[l], A[l], A[l], A[l]};
    
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = merge(segTree[cursor * 2], segTree[cursor * 2 + 1]);
    }
}

Node segQuery(int ql, int qr, int cursor = 1, int l = 1, int r = N) {
    
    if (l > qr || r < ql) return {-INF, -INF, -INF, 0};
    
    else if (l >= ql && r <= qr) return segTree[cursor];
    
    else {
        
        return merge(segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2),
            segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r));
    }
}

void solve() {
    
    segInit();
    
    int M;
    std::cin >> M;
    
    for (int ql, qr; M--; ) {
        
        std::cin >> ql >> qr;
        auto res = segQuery(ql, qr);
        std::cout << std::max(std::max(res.left, res.right), res.mid) << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

