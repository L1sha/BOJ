#include "bits/stdc++.h"

constexpr int N_MAX = 500'001;
constexpr long long DIVIDER = (static_cast<long long>(1) << 32);

int N, Q;

std::array<std::vector<int>, N_MAX> adjL;
std::array<int, N_MAX> nodeNum, nodeParent, nodeHeight, in, revIn, out, top;
std::array<unsigned long long, N_MAX * 4> segTree, lazyA, lazyB;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> Q;
    
    for (int node1, node2, idx = 0; idx < N - 1; ++idx) {
        
        std::cin >> node1 >> node2;
        adjL[node1].push_back(node2);
        adjL[node2].push_back(node1);
    }
    
    std::fill(lazyA.begin(), lazyA.begin() + 4 * N, 1);
}

void initDFS(const int& cursor = 1, const int& parent = 0) {
    
    static int height = 0;
    
    int maxNodeNum = 0;
    nodeNum[cursor] = 1;
    nodeParent[cursor] = parent;
    nodeHeight[cursor] = ++height;
    
    for (auto& next : adjL[cursor]) {
        
        if (next == parent) continue;
        
        initDFS(next, cursor);
        nodeNum[cursor] += nodeNum[next];
        
        if (nodeNum[next] > maxNodeNum) {
            
            maxNodeNum = nodeNum[next];
            std::swap(adjL[cursor].front(), next);
        }
    }
    
    --height;
}

void initDFS2(const int& cursor = 1, const int& parent = 0) {
    
    static int cnt = 0;
    static int curTop = 0;
    static bool isTop = true;
    
    if (isTop) {
        
        isTop = false;
        curTop = cursor;
    }
    
    in[cursor] = ++cnt;
    revIn[in[cursor]] = cursor;
    top[cursor] = curTop;
    
    for (auto& next : adjL[cursor]) {
        
        if (next == parent) continue;
        
        if (next != adjL[cursor].front()) isTop = true;
        
        initDFS2(next, cursor);
    }
    
    out[cursor] = cnt;
}

void lazyUpdate(const int& cursor, const int& l, const int& r) {
    
    segTree[cursor] = (segTree[cursor] * lazyA[cursor]) % DIVIDER;
    segTree[cursor] = (segTree[cursor] + lazyB[cursor] * (r - l + 1)) % DIVIDER;
    
    if (l != r) {
        
        lazyA[cursor * 2] = (lazyA[cursor * 2] * lazyA[cursor]) % DIVIDER;
        lazyB[cursor * 2] = (lazyB[cursor * 2] * lazyA[cursor]) % DIVIDER;
        lazyB[cursor * 2] = (lazyB[cursor * 2] + lazyB[cursor]) % DIVIDER;
        
        lazyA[cursor * 2 + 1] = (lazyA[cursor * 2 + 1] * lazyA[cursor]) % DIVIDER;
        lazyB[cursor * 2 + 1] = (lazyB[cursor * 2 + 1] * lazyA[cursor]) % DIVIDER;
        lazyB[cursor * 2 + 1] = (lazyB[cursor * 2 + 1] + lazyB[cursor]) % DIVIDER;
    }
    
    lazyA[cursor] = 1;
    lazyB[cursor] = 0;
}

void segUpdate(const int& ql, const int& qr, const unsigned long long& A, const unsigned long long& B, const int& cursor = 1, const int& l = 1, const int& r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (l > qr || r < ql) return;
    else if (l >= ql && r <= qr) {
        
        segTree[cursor] = (segTree[cursor] * A) % DIVIDER;
        segTree[cursor] = (segTree[cursor] + B * (r - l + 1)) % DIVIDER;
        
        if (l != r) {
            
            lazyA[cursor * 2] = (lazyA[cursor * 2] * A) % DIVIDER;
            lazyB[cursor * 2] = (lazyB[cursor * 2] * A) % DIVIDER;
            lazyB[cursor * 2] = (lazyB[cursor * 2] + B) % DIVIDER;
            
            lazyA[cursor * 2 + 1] = (lazyA[cursor * 2 + 1] * A) % DIVIDER;
            lazyB[cursor * 2 + 1] = (lazyB[cursor * 2 + 1] * A) % DIVIDER;
            lazyB[cursor * 2 + 1] = (lazyB[cursor * 2 + 1] + B) % DIVIDER;
        }
    }
    else {
        
        segUpdate(ql, qr, A, B, cursor * 2, l, l + (r - l) / 2);
        segUpdate(ql, qr, A, B, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = (segTree[cursor * 2] + segTree[cursor * 2 + 1]) % DIVIDER;
    }
}

long long segQuery(const int& ql, const int& qr, const int& cursor = 1, const int& l = 1, const int& r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (l > qr || r < ql) return 0;
    else if (l >= ql && r <= qr) return segTree[cursor];
    else {
        
        return (segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2)
            + segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r)) % DIVIDER;
    }
}

void updateSubTree(const int& node, const int& A, const int& B) {
    
    segUpdate(in[node], out[node], A, B);
}

void updateRoute(int left, int right, const int& A, const int& B) {
    
    while (top[left] != top[right]) {
        
        if (nodeHeight[top[left]] < nodeHeight[top[right]]) std::swap(left, right);
        
        segUpdate(in[top[left]], in[left], A, B);
        
        left = nodeParent[top[left]];
    }
    
    if (nodeHeight[left] > nodeHeight[right]) std::swap(left, right);
    
    segUpdate(in[left], in[right], A, B);
}

unsigned long long sumSubTree(const int& node) {
    
    return segQuery(in[node], out[node]);
}

unsigned long long sumRoute(int left, int right) {
    
    long long res = 0;
    
    while (top[left] != top[right]) {
        
        if (nodeHeight[top[left]] < nodeHeight[top[right]]) std::swap(left, right);
        
        res = (res + segQuery(in[top[left]], in[left])) % DIVIDER;
        
        left = nodeParent[top[left]];
    }
    
    if (nodeHeight[left] > nodeHeight[right]) std::swap(left, right);
    
    res = (res + segQuery(in[left], in[right])) % DIVIDER;
    
    return res;
}

void solve() {
    
    initDFS();
    initDFS2();
    
    int query, X, Y, V;
    
    while (Q--) {
        
        std::cin >> query >> X;
        
        if (query == 1) {
            
            std::cin >> V;
            
            updateSubTree(X, 1, V);
        }
        else if (query == 2) {
            
            std::cin >> Y >> V;
            
            updateRoute(X, Y, 1, V);
        }
        else if (query == 3) {
            
            std::cin >> V;
            
            updateSubTree(X, V, 0);
        }
        else if (query == 4) {
            
            std::cin >> Y >> V;
            
            updateRoute(X, Y, V, 0);
        }
        else if (query == 5) {
            
            std::cout << sumSubTree(X) << '\n';
        }
        else if (query == 6) {
            
            std::cin >> Y;
            
            std::cout << sumRoute(X, Y) << '\n';
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}