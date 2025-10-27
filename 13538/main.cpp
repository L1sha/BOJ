#include "bits/stdc++.h"

constexpr int M_MAX = 500'000, X_MAX = 500'000, LOGX_MAX = ceil(log2(X_MAX));

int N, M;

struct segNode {
    
    std::array<int, 2> children{-1, -1};
    int cnt = 0;
};

std::vector<segNode> segTree(1);
std::array<int, M_MAX + 1> segRoots;




void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> M;
}

void segInit(int cursor = 0, int l = 0, int r = (1 << LOGX_MAX) - 1) {
    
    if (l != r) {
        
        segTree[cursor].children[0] = segTree.size();
        segTree.push_back({});
        segTree[cursor].children[1] = segTree.size();
        segTree.push_back({});
        
        segInit(segTree[cursor].children[0], l, l + (r - l) / 2);
        segInit(segTree[cursor].children[1], l + (r - l) / 2 + 1, r);
    }
}

void insertQuery1(const int& X) {
    
    ++N;
    segRoots[N] = segTree.size();
    segTree.push_back({});
    
    int prevCursor = segRoots[N - 1], currCursor = segRoots[N];
    
    for (int xCursor, opposite, idx = LOGX_MAX - 1; idx >= 0; --idx) {
        
        xCursor = (X >> idx) & 1;
        opposite = (xCursor + 1) & 1;       
        
        segTree[currCursor].children[opposite] = segTree[prevCursor].children[opposite];
        segTree[currCursor].cnt = segTree[prevCursor].cnt + 1;
        segTree[currCursor].children[xCursor] = segTree.size();
        segTree.push_back({});
        
        prevCursor = segTree[prevCursor].children[xCursor];
        currCursor = segTree[currCursor].children[xCursor];
    }
    
    segTree[currCursor].cnt = segTree[prevCursor].cnt + 1;
}

int printQuery2(const int& L, const int& R, const int& X) {
    
    int prevCursor = segRoots[L - 1], currCursor = segRoots[R], res = 0;
    
    for (int next, xCursor, opposite, idx = LOGX_MAX - 1; idx >= 0; --idx) {
        
        xCursor = (X >> idx) & 1;
        opposite = (xCursor + 1) & 1;       
        
        if (segTree[segTree[prevCursor].children[opposite]].cnt
            < segTree[segTree[currCursor].children[opposite]].cnt) {
            
            next = opposite;
        }
        else {
            
            next = xCursor;
        }
        
        prevCursor = segTree[prevCursor].children[next];
        currCursor = segTree[currCursor].children[next];
        res += (next ? (1 << idx) : 0);
    }
    
    return res;
}

void deleteQuery3(const int& K) {
    
    N -= K;
}

int segQuery4(const int& X, int prevCursor, int currCursor,
    int l = 0, int r = (1 << LOGX_MAX) - 1) {
    
    if (l > X) return 0;
    else if (r <= X) return segTree[currCursor].cnt - segTree[prevCursor].cnt;
    else {
        
        return segQuery4(X, segTree[prevCursor].children[0],
            segTree[currCursor].children[0], l, l + (r - l) / 2)
            + segQuery4(X, segTree[prevCursor].children[1],
            segTree[currCursor].children[1], l + (r - l) / 2 + 1, r);
    }
}

int printQuery4(const int& L, const int& R, const int& X) {
    
    return segQuery4(X, segRoots[L - 1], segRoots[R]);
}

int segQuery5(int K, int prevCursor, int currCursor,
    int l = 0, int r = (1 << LOGX_MAX) - 1) {
    
    if (l == r) return l;
    
    const auto& prev0 = segTree[prevCursor].children[0];
    const auto& prev1 = segTree[prevCursor].children[1];
    const auto& curr0 = segTree[currCursor].children[0];
    const auto& curr1 = segTree[currCursor].children[1];
    
    if (int lDiff = segTree[curr0].cnt - segTree[prev0].cnt; lDiff < K) {
        
        return segQuery5(K - lDiff, prev1, curr1, l + (r - l) / 2 + 1, r);
    }
    else {
        
        return segQuery5(K, prev0, curr0, l, l + (r - l) / 2);
    }
}

int printQuery5(const int& L, const int& R, const int& K) {
    
    return segQuery5(K, segRoots[L - 1], segRoots[R]);
}

void solve() {
    
    segInit();
    
    for (int qType, L, R, X, K; M--; ) {
        
        std::cin >> qType;
        
        switch (qType) {
            
            case 1:
            std::cin >> X;
            insertQuery1(X);
            break;
            
            case 2:
            std::cin >> L >> R >> X;
            std::cout << printQuery2(L, R, X) << '\n';
            break;
            
            case 3:
            std::cin >> K;
            deleteQuery3(K);
            break;
            
            case 4:
            std::cin >> L >> R >> X;
            std::cout << printQuery4(L, R, X) << '\n';
            break;
            
            case 5:
            std::cin >> L >> R >> K;
            std::cout << printQuery5(L, R, K) << '\n';
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