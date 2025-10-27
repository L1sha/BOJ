#include "bits/stdc++.h"

constexpr int N_MAX = 50'000, M_MAX = 250'000;

int N, M;

std::array<int, N_MAX> in, parent;
std::array<std::vector<int>, N_MAX> adjL;
std::bitset<N_MAX> visited;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

int getParent(int cursor) {
    
    if (cursor == parent[cursor]) return cursor;
    return parent[cursor] = getParent(parent[cursor]);
}

void doUnion(int cursor1, int cursor2) {
    
    parent[getParent(cursor2)] = getParent(cursor1);
}

bool get_input() {
    
    std::cin >> N >> M;
    std::vector<std::pair<int, int>> input; 
    input.reserve(M);
    
    std::iota(parent.begin(), parent.begin() + N, 0);
    
    int K, L;
    char C;
    
    while (M--) {
        
        std::cin >> K >> C >> L;
        
        if (C == '=') doUnion(K, L);
        else input.push_back({K, L});
    }
    
    for (const auto& [k, l] : input) {
        
        int pK = getParent(k), pL = getParent(l);
        
        if (pK == pL) {
            
            std::cout << "inconsistent";
            return false;
        }
        
        adjL[pK].push_back(pL);
        ++in[pL];
    }
    
    return true;
}

void visit(int cursor) {
    
    std::queue<int> q;
    q.push(cursor);
    
    while (!q.empty()) {
        
        cursor = q.front();
        visited[cursor] = true;
        q.pop();
        
        for (const auto& next : adjL[cursor]) {
            
            if (--in[next] == 0) q.push(next);
        }
    }
}

void solve() {
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (!visited[idx] && in[idx] == 0) {
            
            visit(idx);
        }
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (!visited[idx]) {
            
            std::cout << "inconsistent";
            return;
        }
    }
    
    std::cout << "consistent";
}



int main(int argc, char** argv) {
    
    fastIO();
    if (get_input()) solve();
    
    return 0;
}