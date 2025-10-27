#include "bits/stdc++.h"

constexpr int N_MAX = 401, M_MAX = 401;
const int INF = 1e9;

int N, M;

std::array<std::vector<int>, N_MAX + M_MAX> adjL;
std::array<std::array<int, N_MAX + M_MAX>, N_MAX + M_MAX> capa, flow, dist;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    for (int idx = 1, workNum, work, cost; idx <= N; ++idx) {
        
        std::cin >> workNum;
        
        while (workNum--) {
            
            std::cin >> work;
            
            adjL[idx].push_back(N + work);
            capa[idx][N + work] = 1;
            adjL[N + work].push_back(idx);
            
            std::cin >> dist[idx][N + work];
            dist[N + work][idx] = -dist[idx][N + work];
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        adjL[0].push_back(idx);
        capa[0][idx] = 1;
        adjL[idx].push_back(0);
    }
    
    for (int idx = 1; idx <= M; ++idx) {
        
        adjL[N + idx].push_back(N + M + 1);
        capa[N + idx][N + M + 1] = 1;
        adjL[N + M + 1].push_back(N + idx);
    }
}

void solve(int source = 0, int sink = N + M + 1) {
    
    int totalFlow = 0, totalCost = 0;
    
    std::bitset<N_MAX + M_MAX> inQueue;
    std::vector<int> prev(N_MAX + M_MAX), distSum(N_MAX + M_MAX);
    
    while (true) {
        
        inQueue.reset();
        std::fill(prev.begin(), prev.end(), -1);
        std::fill(distSum.begin(), distSum.end(), INF);
        
        std::queue<int> q;
        q.push(source);
        
        inQueue[source] = true;
        prev[source] = source;
        distSum[source] = 0;
        
        for (int cursor; !q.empty();) {
            
            cursor = q.front();
            q.pop();
            inQueue[cursor] = false;
            
            for (const int& next : adjL[cursor]) {
                
                if (flow[cursor][next] < capa[cursor][next] && distSum[next] > distSum[cursor] + dist[cursor][next]) {
                    
                    prev[next] = cursor;
                    distSum[next] = distSum[cursor] + dist[cursor][next];
                    
                    if (!inQueue[next]) {
                        
                        inQueue[next] = true;
                        q.push(next);
                    }
                }
            }
        }
        
        if (prev[sink] == -1) break;
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            flow[prev[cursor]][cursor]++;
            flow[cursor][prev[cursor]]--;
        }
        
        totalFlow++;
        totalCost += distSum[sink];
    }
    
    std::cout << totalFlow << '\n' << totalCost;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

