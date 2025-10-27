#include "bits/stdc++.h"

constexpr int N_MAX = 100'001, LOGN_MAX = ceil(log2(N_MAX));

struct segNode {
    
    int val, lIdx, rIdx;
};

int N, M, cnt;

std::array<std::pair<int, int>, N_MAX> A, AToBeSorted;
std::array<segNode, N_MAX * 4 + N_MAX * LOGN_MAX> segTree;
std::array<int, N_MAX> rootNodes;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> AToBeSorted[idx].first;
        AToBeSorted[idx].second = idx;
    }
}

void segInit(int cursor = 0, int l = 1, int r = N) {
    
    if (l == r) segTree[cursor] = {0, -1, -1};
    else {
        
        segTree[cursor] = {0, cnt, cnt + 1};
        cnt += 2;
        
        segInit(segTree[cursor].lIdx, l, l + (r - l) / 2);
        segInit(segTree[cursor].rIdx, l + (r - l) / 2 + 1, r);
    }
}

void addPST(int newIdx, int newCursor, int lastCursor, int l = 1, int r = N) {
    
    if (l == r) segTree[newCursor] = {1, -1, -1};
    else {
        
        segTree[newCursor].val = segTree[lastCursor].val + 1;
        
        if (A[newIdx].second <= l + (r - l) / 2) {
            
            segTree[newCursor].lIdx = cnt++;
            segTree[newCursor].rIdx = segTree[lastCursor].rIdx;
            
            addPST(newIdx, segTree[newCursor].lIdx, segTree[lastCursor].lIdx,
                l, l + (r - l) / 2);
        }
        else {
            
            segTree[newCursor].lIdx = segTree[lastCursor].lIdx;
            segTree[newCursor].rIdx = cnt++;
            
            addPST(newIdx, segTree[newCursor].rIdx, segTree[lastCursor].rIdx,
                l + (r - l) / 2 + 1, r);
        }
    }
}

void init() {
    
    std::sort(AToBeSorted.begin() + 1, AToBeSorted.begin() + N + 1);
    
    for (int idx = 1; idx <= N; ++idx) {
        
        A[AToBeSorted[idx].second] = {AToBeSorted[idx].first, idx};
    }
    
    rootNodes[0] = 0;
    cnt = 1;
    segInit();
    
    for (int idx = 1; idx <= N; ++idx) {
        
        rootNodes[idx] = cnt++;
        addPST(idx, rootNodes[idx], rootNodes[idx - 1]);
    }
}

int segQuery(int K, int cursor1, int cursor2, int l = 1, int r = N) {
    
    if (l == r) return l;
    else {
        
        if (K <= segTree[segTree[cursor2].lIdx].val - segTree[segTree[cursor1].lIdx].val) {
            
            return segQuery(K, segTree[cursor1].lIdx, segTree[cursor2].lIdx,
                l, l + (r - l) / 2);
        }
        else {
            
            return segQuery(K - segTree[segTree[cursor2].lIdx].val + segTree[segTree[cursor1].lIdx].val,
                segTree[cursor1].rIdx, segTree[cursor2].rIdx,
                l + (r - l) / 2 + 1, r);
        }
    }
}

int query(const int& I, const int& J, const int& K) {
    
    return AToBeSorted[segQuery(K, rootNodes[I - 1], rootNodes[J])].first;
}

void solve() {
    
    init();
    
    for (int I, J, K; M--; ) {
        
        std::cin >> I >> J >> K;
        
        std::cout << query(I, J, K) << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}