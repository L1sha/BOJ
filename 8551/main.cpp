#include "bits/stdc++.h"

constexpr int N_MAX = 10'001;

int N, M;

struct Edge {
    
    int dest;
    bool able;
    int revIdx;
    
    Edge(int d, bool a, int r) : dest(d), able(a), revIdx(r) {}
};

std::array<std::vector<Edge>, N_MAX> adjL;
std::array<int, N_MAX> level, work;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    for (int from, to; M--; ) {
        
        std::cin >> from >> to;
        
        adjL[from].emplace_back(to, true, adjL[to].size());
        adjL[to].emplace_back(from, false, adjL[from].size() - 1);
    }
}

bool BFS() {
    
    std::fill(level.begin() + 1, level.begin() + N + 1, -1);
    std::fill(work.begin() + 1, work.begin () + N + 1, 0);
    
    std::queue<int> q;
    q.push(1);
    level[1] = 0;
    
    for (int cursor; !q.empty(); ) {
        
        cursor = q.front();
        q.pop();
        
        for (const auto& [dest, able, rev] : adjL[cursor]) {
            
            if (able && level[dest] == -1) {
                
                level[dest] = level[cursor] + 1;
                q.push(dest);
            }
        }
    }
    
    return level[N] != -1;
}

bool DFS(int cursor = 1) {
    
    if (cursor == N) return true;
    
    for (; work[cursor] < adjL[cursor].size(); ++work[cursor]) {
        
        auto& [next, able, rev] = adjL[cursor][work[cursor]];
        auto& revAble = adjL[next][rev].able;
        
        if (able && level[next] == level[cursor] + 1) {
            
            if (DFS(next)) {
                
                able = false;
                revAble = true;
                
                return true;
            }
        }
    }
    
    return false;
}

void solve() {
    
    int res = 0;
    
    while (BFS()) {
        
        while (DFS()) ++res;
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}