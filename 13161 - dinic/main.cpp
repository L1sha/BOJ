#include "bits/stdc++.h"

constexpr int N_MAX = 501;

int N;

std::vector<int> A, B, dontCare;
std::array<std::array<int, N_MAX>, N_MAX> W;
std::array<std::vector<int>, N_MAX + 1> adjL;
std::array<std::array<int, N_MAX + 1>, N_MAX + 1> flow, capa;
std::array<int, N_MAX + 1> dist, work;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    A.reserve(N);
    B.reserve(N);
    dontCare.reserve(N);
    
    for (int color, idx = 1; idx <= N; ++idx) {
        
        std::cin >> color;
        
        switch (color) {
            
            case 0:
            dontCare.push_back(idx);
            
            break;
            
            case 1:
            A.push_back(idx);
            
            break;
            
            case 2:
            B.push_back(idx);
            
            break;
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        for (int idx2 = 1; idx2 <= N; ++idx2) {
            
            std::cin >> W[idx][idx2];
        }
    }
}

bool getDist(const int& source, const int& sink) {
    
    // BFS
    
    std::fill(dist.begin(), dist.begin() + N + 2, -1);
    std::fill(work.begin(), work.begin() + N + 2, 0);
    
    std::queue<int> q;
    q.push(source);
    dist[source] = 0;
    
    for (int cursor; !q.empty(); ) {
        
        cursor = q.front();
        q.pop();
        
        for (const int& next : adjL[cursor]) {
            
            if (dist[next] == -1 && flow[cursor][next] < capa[cursor][next]) {
                
                dist[next] = dist[cursor] + 1;
                q.push(next);
            }
        }
    }
    
    return dist[sink] != -1;
}

int getBlockingFlow(const int& cursor, const int& sink, int maxflow) {
    
    if (cursor == sink) return maxflow;
    
    for (int& idx = work[cursor]; idx < adjL[cursor].size(); ++idx) {
        
        int next = adjL[cursor][idx];
        
        if (dist[next] == dist[cursor] + 1 && flow[cursor][next] < capa[cursor][next]) {
            
            int newFlow = getBlockingFlow(next, sink, std::min(maxflow, capa[cursor][next] - flow[cursor][next]));
            
            if (newFlow) {
                
                flow[cursor][next] += newFlow;
                flow[next][cursor] -= newFlow;
                
                return newFlow;
            }
        }
    }
    
    return 0;
}

void solve() {
    
    int source = 0, sink = N + 1;
    
    for (const int& dc : dontCare) {
        
        adjL[source].push_back(dc);
        adjL[dc].push_back(source);
        
        for (const int& a : A) {
            
            capa[source][dc] += W[a][dc];
        }
        
        adjL[dc].push_back(sink);
        adjL[sink].push_back(dc);
        
        for (const int& b : B) {
            
            capa[dc][sink] += W[dc][b];
        }
    }
    
    for (auto it1 = dontCare.begin(); it1 != dontCare.end(); ++it1) {
        
        for (auto it2 = it1 + 1; it2 != dontCare.end(); ++it2) {
            
            adjL[*it1].push_back(*it2);
            capa[*it1][*it2] = W[*it1][*it2];
            adjL[*it2].push_back(*it1);
            capa[*it2][*it1] = W[*it2][*it1];
        }
    }
    
    std::vector<int> prev(N + 2);
    int totalFlow = 0;
    
    while (true) {
        
        if (!getDist(source, sink)) break;
        
        while (true) {
            
            int newFlow = getBlockingFlow(source, sink, INT_MAX);
            
            if (newFlow == 0) break;
            
            totalFlow += newFlow;
        }
    }
    
    for (const int& a : A) {
        
        for (const int& b : B) {
            
            totalFlow += W[a][b];
        }
    }
    
    for (const int& dc : dontCare) {
        
        if (dist[dc] == -1) B.push_back(dc);
        else A.push_back(dc);
    }
    
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    
    std::cout << totalFlow << '\n';
    
    for (const auto& a : A) std::cout << a << ' ';
    std::cout << '\n';
    
    for (const auto& b : B) std::cout << b << ' ';
    std::cout << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

