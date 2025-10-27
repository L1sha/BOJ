#include "bits/stdc++.h"

constexpr int N_MAX = 200'001, M_MAX = 200'001, PRIME = 1'000'000'007;

int N, M, C;

std::array<std::vector<int>, N_MAX> adjL;
std::array<int, N_MAX> in, revIn, out, color;
std::array<std::vector<int>, 4 * N_MAX> segTree;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> C;
    for (int idx = 1; idx <= N; ++idx) std::cin >> color[idx];
    for (int node1, node2, idx = 0; idx < N - 1; ++idx) {
        
        std::cin >> node1 >> node2;
        adjL[node1].push_back(node2);
        adjL[node2].push_back(node1);
    }
}

void DFS(int curr = 1, int prev = 0) {
    
    static int cnt = 0;
    
    in[curr] = ++cnt;
    revIn[in[curr]] = curr;
    
    for (const int& next : adjL[curr]) {
        
        if (prev != next) {
            
            DFS(next, curr);
        }
    }
    
    out[curr] = cnt;
}

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) segTree[cursor] = {color[revIn[l]]};
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor].resize(segTree[cursor * 2].size()
            + segTree[cursor * 2 + 1].size());
        
        std::merge(segTree[cursor * 2].begin(), segTree[cursor * 2].end(),
            segTree[cursor * 2 + 1].begin(), segTree[cursor * 2 + 1].end(),
            segTree[cursor].begin());
    }
}

int segQuery(const int& ql, const int& qr, const int& val,
    int cursor = 1, int l = 1, int r = N) {
    
    if (l > qr || r < ql) return 0;
    else if (l >= ql && r <= qr) {
        
        return std::distance(segTree[cursor].begin(), std::upper_bound(
            segTree[cursor].begin(), segTree[cursor].end(), val));
    }
    else {
        
        return segQuery(ql, qr, val, cursor * 2, l, l + (r - l) / 2)
            + segQuery(ql, qr, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void solve() {
    
    DFS();
    segInit();
    
    int res = 0;
    
    for (int V, C; M--; ) {
        
        std::cin >> V >> C;
        res = (res + segQuery(in[V], out[V], C)) % PRIME;
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}