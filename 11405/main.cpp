#include "bits/stdc++.h"

constexpr int N_MAX = 101, M_MAX = 101;
const int INF = 1e9;

int N, M;

std::array<std::array<int, N_MAX + M_MAX>, N_MAX + M_MAX> flow, capa, cost;
std::array<std::vector<int>, N_MAX + M_MAX> adjL;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        adjL[0].push_back(idx);
        std::cin >> capa[0][idx];
        adjL[idx].push_back(0);
    }
    
    for (int idx = 1; idx <= M; ++idx) {
        
        adjL[N + idx].push_back(N + M + 1);
        std::cin >> capa[N + idx][N + M + 1];
        adjL[N + M + 1].push_back(N + idx);
    }
    
    for (int bookStore = 1; bookStore <= M; ++bookStore) {
        
        for (int person = 1; person <= N; ++person) {
            
            adjL[person].push_back(N + bookStore);
            capa[person][N + bookStore] = INF;
            adjL[N + bookStore].push_back(person);
            
            std::cin >> cost[person][N + bookStore];
            cost[N + bookStore][person] = -cost[person][N + bookStore];
        }
    }
}

void solve(int source = 0, int sink = N + M + 1) {
    
    std::vector<int> prev(N + M + 2), costSum(N + M + 2);
    std::bitset<N_MAX + M_MAX> inQueue;
    int totalCost = 0;
    
    while (true) {
        
        std::fill(prev.begin(), prev.end(), -1);
        std::fill(costSum.begin(), costSum.end(), INF);
        inQueue.reset();
        
        std::queue<int> q;
        q.push(source);
        
        prev[source] = source;
        costSum[source] = 0;
        inQueue[source] = true;
        
        for (int cursor; !q.empty();) {
            
            cursor = q.front();
            q.pop();
            inQueue[cursor] = false;
            
            for (const int& next : adjL[cursor]) {
                
                if (flow[cursor][next] < capa[cursor][next] && costSum[cursor] + cost[cursor][next] < costSum[next]) {
                    
                    costSum[next] = costSum[cursor] + cost[cursor][next];
                    prev[next] = cursor;
                    
                    if (!inQueue[next]) {
                        
                        q.push(next);
                        inQueue[next] = true;
                    }
                }
            }
        }
        
        if (prev[sink] == -1) break;
        
        int maxFlow = INF;
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            maxFlow = std::min(maxFlow, capa[prev[cursor]][cursor] - flow[prev[cursor]][cursor]);
        }
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            flow[prev[cursor]][cursor] += maxFlow;
            flow[cursor][prev[cursor]] -= maxFlow;
            totalCost += cost[prev[cursor]][cursor] * maxFlow;
        }
    }
    
    std::cout << totalCost;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

