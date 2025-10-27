#include "bits/stdc++.h"

constexpr int N_MAX = 200'001;

int N, Q;

std::array<int, N_MAX> parent;
std::array<std::vector<int>, N_MAX> children;
std::vector<std::vector<bool>> segTree(1);
std::vector<std::vector<int>> segCoordToNode(1);
std::vector<std::pair<int, int>> topNode(1, {0, 0});
std::array<std::pair<int, int>, N_MAX> nodeToSegCoord;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> Q;
    
    for (int idx = 2; idx <= N; ++idx) {
        
        std::cin >> parent[idx];
        children[parent[idx]].push_back(idx);
    }
}

int DFS1(int cursor = 1) {
    
    int maxNodeNum = 0, totalNodeNum = 1;
    
    for (auto& child : children[cursor]) {
        
        auto temp = DFS1(child);
        totalNodeNum += temp;
        
        if (temp > maxNodeNum) {
            
            maxNodeNum = temp;
            std::swap(children[cursor].front(), child);
        }
    }
    
    return totalNodeNum;
}

void DFS2(int cursor = 1) {
    
    nodeToSegCoord[cursor] = {segCoordToNode.size() - 1, segCoordToNode.back().size()};
    segCoordToNode.back().push_back(cursor);
    
    for (const auto& child : children[cursor]) {
        
        if (child == children[cursor].front()) {
            
            DFS2(child);
        }
        else {
            
            segTree.push_back({});
            segCoordToNode.push_back({});
            topNode.push_back(nodeToSegCoord[cursor]);
            
            DFS2(child);
        }
    }
}

void segInit() {
    
    for (int idx = 0; idx < segTree.size(); ++idx) {
        
        segTree[idx].resize(segCoordToNode[idx].size() * 4, true);
    }
}

void segUpdate(const int& tIdx, const int& target, int cursor, int l, int r) {
    
    if (target > r || target < l) return;
    
    segTree[tIdx][cursor] = false;
    
    if (l != r) {
        
        segUpdate(tIdx, target, cursor * 2, l, l + (r - l) / 2);
        segUpdate(tIdx, target, cursor * 2 + 1, l + (r - l) / 2 + 1 , r);
    }
}

bool segQuery(const int& tIdx, const int& ql, const int& qr, int cursor, int l, int r) {
    
    if (l > qr || r < ql) return true;
    else if (l >= ql && r <= qr) return segTree[tIdx][cursor];
    else {
        
        return segQuery(tIdx, ql, qr, cursor * 2, l, l + (r - l) / 2)
            & segQuery(tIdx, ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void update(const int& cursor) {
    
    if (parent[cursor]) {
        
        segUpdate(nodeToSegCoord[cursor].first, nodeToSegCoord[cursor].second,
            1, 0, segCoordToNode[nodeToSegCoord[cursor].first].size() - 1);
        
        parent[cursor] = 0;
    }
}

bool query(const int& left, const int& right) {
    
    auto [l1, l2] = nodeToSegCoord[left];
    auto [r1, r2] = nodeToSegCoord[right];
    
    while (l1 != r1) {
        
        if (l1 > r1) {
            
            std::swap(l1, r1);
            std::swap(l2, r2);
        }
        
        if (!segQuery(r1, 0, r2, 1, 0, segCoordToNode[r1].size() - 1)) return false;
        
        r2 = topNode[r1].second;
        r1 = topNode[r1].first;
    }
    
    if (l2 == r2) return true;
    else {
        
        if (l2 > r2) std::swap(l2, r2);
        
        return segQuery(l1, l2 + 1, r2, 1, 0, segCoordToNode[l1].size() - 1);
    }
}

void solve() {
    
    DFS1();
    DFS2();
    segInit();
    
    for (int B, C, D; Q--; ) {
        
        std::cin >> B >> C >> D;
        
        auto res = query(B, C);
        
        if (res) std::cout << "YES\n";
        else std::cout << "NO\n";
        
        if (D) {
            
            if (res) update(B);
            else update(C);
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}