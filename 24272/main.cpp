#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N, cnt;

std::array<std::vector<int>, N_MAX> adjL;
std::array<int, N_MAX> parent, in, out, dirrStatus;
std::array<std::pair<int, int>, N_MAX * 4> segTree;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void DFS(int curr = 1, int prev = 0) {
    
    parent[curr] = prev;
    in[curr] = ++cnt;
    
    for (const auto& next : adjL[curr]) {
        
        if (next != prev) {
            
            DFS(next, curr);
        }
    }
    
    out[curr] = cnt;
}

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    segTree[cursor] = {0, r - l + 1};
    
    if (l != r) {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void segUpdate(const int& ql, const int& qr, const int& val,
    int cursor = 1, int l = 1, int r = N) {
    
    if (l > qr || r < ql) return;
    else if (l >= ql && r <= qr) {
        
        segTree[cursor].first += val;
    }
    else {
        
        segUpdate(ql, qr, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate(ql, qr, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor].second =
            (segTree[cursor * 2].first ? 0 : segTree[cursor * 2].second) +
            (segTree[cursor * 2 + 1].first ? 0 : segTree[cursor * 2 + 1].second); 
    }
}

void update(int node, int dirr) {
    
    if (dirrStatus[node] == dirr) return;
    
    if (dirrStatus[node] == 1) {
        
        segUpdate(in[node], out[node], -1);
    }
    else if (dirrStatus[node] == 2) {
        
        if (in[node] != 1) {
            
            segUpdate(1, in[node] - 1, -1);
        }
        
        if (out[node] != N) {
            
            segUpdate(out[node] + 1, N, -1);
        }
    }
    
    if (dirr == 1) {
        
        segUpdate(in[node], out[node], 1);
    }
    else if (dirr == 2) {
        
        if (in[node] != 1) {
            
            segUpdate(1, in[node] - 1, 1);
        }
        
        if (out[node] != N) {
            
            segUpdate(out[node] + 1, N, 1);
        }
    }
    
    dirrStatus[node] = dirr;
}

void get_input() {
    
    std::cin >> N;
    
    int from, to;
    std::string dir;
    std::vector<std::pair<int, int>> dirrQuery;
    
    for (int idx = 0; idx < N - 1; ++idx) {
        
        std::cin >> from >> dir >> to;
        
        adjL[from].push_back(to);
        adjL[to].push_back(from);
        
        if (dir == "<-") {
            
            dirrQuery.push_back({from, to});
        }
        else if (dir == "->") {
            
            dirrQuery.push_back({to, from});
        }
    }
    
    DFS();
    segInit();
    
    for (const auto& [node1, node2] : dirrQuery) {
        
        // node1 <- node2
        
        if (parent[node1] == node2) {
            
            update(node1, 1);
        }
        else {  // parent[node2] == node1
            
            update(node2, 2);
        }
    }
}

int query() {
    
    return (segTree[1].first ? 0 : segTree[1].second);
}

void solve() {
    
    int Q, from, to, dirr;
    std::string dir;
    std::cin >> Q;
    
    while (Q--) {
        
        std::cin >> from >> dir >> to;
        
        if (dir == "--") dirr = 0;
        else if (dir == "<-") dirr = 1;
        else dirr = 2;
        
        if (parent[from] != to) {   // parent[to] == from
            
            std::swap(from, to);
            
            if (dirr) dirr = dirr % 2 + 1; // 1 -> 2, 2 -> 1
        }
        
        update(from, dirr);
        
        std::cout << query() << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}