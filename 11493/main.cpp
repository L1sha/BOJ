#include "bits/stdc++.h"

constexpr int N_MAX = 500;

const int INF = 1e9;

int N, M, source = 0, sink;

std::array<std::vector<int>, N_MAX + 2> adjL;
std::array<std::array<int, N_MAX + 2>, N_MAX + 2> flow, capa;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    sink = N + 1;
    
    for (int idx = 0; idx < N + 2; ++idx) adjL[idx].clear();
    
    for (int from, to; M--; ) {
        
        std::cin >> from >> to;
        
        adjL[from].push_back(to);
        capa[from][to] = INF;
        flow[from][to] = 0;
        
        adjL[to].push_back(from);
        capa[to][from] = INF;
        flow[to][from] = 0;
    }
    
    for (int color, idx = 1; idx <= N; ++idx) {
        
        std::cin >> color;
        
        if (color) {
            
            adjL[idx].push_back(sink);
            capa[idx][sink] = 1;
            flow[idx][sink] = 0;
        }
    }
    
    for (int color, idx = 1; idx <= N; ++idx) {
        
        std::cin >> color;
        
        if (color) {
            
            adjL[source].push_back(idx);
            capa[source][idx] = 1;
            flow[source][idx] = 0;
        }
    }
}

void solve() {
    
    int totalCost = 0;
    std::vector<int> dist(N + 2), prev(N + 2);
    std::vector<bool> inQueue(N + 2);
    
    while (true) {
        
        std::fill(dist.begin(), dist.end(), INF);
        std::fill(prev.begin(), prev.end(), -1);
        
        std::queue<int> q;
        q.push(source);
        dist[source] = 0;
        
        for (int cursor, d; !q.empty(); ) {
            
            cursor = q.front();
            q.pop();
            inQueue[cursor] = false;
            
            for (const int& next : adjL[cursor]) {
                
                if (cursor == source || next == sink) d = 0;
                else if (flow[cursor][next] < 0) d = -1;
                else d = 1;
                
                if (flow[cursor][next] < capa[cursor][next] && dist[cursor] + d < dist[next]) {
                    
                    dist[next] = dist[cursor] + d;
                    prev[next] = cursor;
                    
                    if (!inQueue[next]) {
                        
                        q.push(next);
                        inQueue[next] = true;
                    }
                }
            }
        }
        
        if (prev[sink] == -1) break;
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            flow[prev[cursor]][cursor]++;
            flow[cursor][prev[cursor]]--;
        }
        
        totalCost += dist[sink];
    }
    
    std::cout << totalCost << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    
    int T;
    std::cin >> T;
    
    while (T--) {
        
        get_input();
        solve();
    }
    
    return 0;
}

