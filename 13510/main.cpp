#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N;

struct Edge {
    
    int dest = 0, cost, idx;
};

std::array<std::vector<Edge>, N_MAX> adjL;
std::array<int, N_MAX> nodeNum, nodeHeight;
std::array<Edge, N_MAX> maxEdge;
std::array<std::pair<int, int>, N_MAX> nodeLocation, edgeLocation;
std::vector<std::vector<int>> realNode, toBeSeg, segTrees;
std::vector<std::pair<int, int>> segHead;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int node1, node2, cost, idx = 1; idx <= N - 1; ++idx) {
        
        std::cin >> node1 >> node2 >> cost;
        
        adjL[node1].push_back({node2, cost, idx});
        adjL[node2].push_back({node1, cost, idx});
    }
}

void initDFS(int curNode = 1, int prevNode = 0, int height = 0) {
    
    nodeNum[curNode] = 1;
    nodeHeight[curNode] = height;
    
    int maxNode = 0;
    
    for (const auto& [dest, cost, idx] : adjL[curNode]) {
        
        if (dest != prevNode) {
            
            initDFS(dest, curNode, height + 1);
            nodeNum[curNode] += nodeNum[dest];
            
            if (nodeNum[dest] > maxNode) {
                
                maxNode = nodeNum[dest];
                maxEdge[curNode] = {dest, cost, idx};
            }
        }
    }
}

void segInit(int order, int cursor, int l, int r) {
    
    if (l == r) {
        
        segTrees[order][cursor] = toBeSeg[order][l];
    }
    else {
        
        segInit(order, cursor * 2, l, l + (r - l) / 2);
        segInit(order, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTrees[order][cursor] = std::max(segTrees[order][cursor * 2], segTrees[order][cursor * 2 + 1]);
    }
}

void initDFS2(int curNode = 1, int prevNode = 0, int prevCost = 0, int prevIdx = 0) {
    
    if (!prevNode) {
        
        nodeLocation[curNode] = {-1, 0};
        
        segHead.push_back(nodeLocation[curNode]);
        toBeSeg.resize(1);
        realNode.resize(1);
    }
    else {
        
        nodeLocation[curNode] = {toBeSeg.size() - 1, toBeSeg.back().size()};
        edgeLocation[prevIdx] = nodeLocation[curNode];
        
        toBeSeg.back().push_back(prevCost);
        realNode.back().push_back(curNode);
    }
    
    if (adjL[curNode].size() != 1 || !prevNode) {
        
        initDFS2(maxEdge[curNode].dest, curNode, maxEdge[curNode].cost, maxEdge[curNode].idx);
        
        for (const auto& [dest, cost, idx] : adjL[curNode]) {
            
            if (dest != prevNode && dest != maxEdge[curNode].dest) {
                
                segHead.push_back(nodeLocation[curNode]);
                toBeSeg.push_back({});
                realNode.push_back({});
                initDFS2(dest, curNode, cost, idx);
            }
        }
    }
    else {
        
        segTrees.push_back(std::vector<int>(4 * toBeSeg.back().size()));
        segInit(toBeSeg.size() - 1, 1, 0, toBeSeg.back().size() - 1);
    }
}

void segUpdate(const int& order, const int& target, const int& val, int cursor, int l, int r) {
    
    if (l > target || r < target) return;
    else if (l == r) segTrees[order][cursor] = val;
    else {
        
        segUpdate(order, target, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate(order, target, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTrees[order][cursor] = std::max(segTrees[order][cursor * 2], segTrees[order][cursor * 2 + 1]);
    }
}

void Update(const int& target, const int& val) {
    
    segUpdate(edgeLocation[target].first, edgeLocation[target].second, val, 1, 0, toBeSeg[edgeLocation[target].first].size() - 1);
}

int segQuery(const int& order, const int& ql, const int& qr, int cursor, int l, int r) {
    
    if (l > qr || r < ql) return 0;
    else if (l >= ql && r <= qr) return segTrees[order][cursor];
    else {
        
        return std::max(segQuery(order, ql, qr, cursor * 2, l, l + (r - l) / 2),
            segQuery(order, ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r));
    }
}

int Query(const int& Node1, const int& Node2) {
    
    if (Node1 == Node2) return 0;
    
    int res = 0;
    std::pair<int, int> left = nodeLocation[Node1], right = nodeLocation[Node2];
    
    while (left.first != right.first) {
        
        if (left.first == -1) {
            
            std::swap(left, right);
        }
        else if (right.first != -1 && nodeHeight[realNode[left.first][left.second]] < nodeHeight[realNode[right.first][right.second]]) {
            
            std::swap(left, right);
        }
        
        res = std::max(res, segQuery(left.first, 0, left.second, 1, 0, toBeSeg[left.first].size() - 1));
        left = segHead[left.first];
    }
    
    if (left.first != -1 && left.second != right.second) {
        
        res = std::max(res, segQuery(left.first, std::min(left.second, right.second) + 1, std::max(left.second, right.second), 1, 0, toBeSeg[left.first].size() - 1));
    }
    
    return res;
}

void solve() {
    
    initDFS();
    initDFS2();
    
    int M, Q, U, V; std::cin >> M;
    
    while (M--) {
        
        std::cin >> Q >> U >> V;
        
        if (Q == 1) Update(U, V);
        else std::cout << Query(U, V) << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

