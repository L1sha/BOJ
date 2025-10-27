#include "bits/stdc++.h"

constexpr int V_MAX = 2001;
const int INF = 1e9;

int V, E;
std::array<std::array<int, V_MAX>, V_MAX> capa, flow, cost;
std::array<std::vector<int>, V_MAX> adjL;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

bool get_input() {
    
    if (std::cin >> V >> E) {
        
        for (int idx = 1; idx <= 2 * V; ++idx) {
            
            for (int idx2 = 1; idx2 <= 2 * V; ++idx2) {
                
                capa[idx][idx2] = 0;
                flow[idx][idx2] = 0;
                cost[idx][idx2] = 0;
            }
            
            adjL[idx].clear();
        }
        
        for (int A, B, C; E--;) {
            
            std::cin >> A >> B >> C;
            
            if (cost[A][B + V]) {
                
                cost[A][B + V] = std::min(cost[A][B + V], C);
                cost[B + V][A] = std::max(cost[B + V][A], -C);
            }
            else {
                
                adjL[A].push_back(B + V);
                capa[A][B + V] = 1;
                cost[A][B + V] = C;
                adjL[B + V].push_back(A);
                cost[B + V][A] = -C;
            }
        }
        
        for (int idx = 1; idx <= V; ++idx) {
            
            adjL[idx + V].push_back(idx);
            capa[idx + V][idx] = 1;
            adjL[idx].push_back(idx + V);
        }
        
        return true;
    }
    
    return false;
}

void solve() {
    
    std::vector<int> prev(2 * V + 1), costSum(2 * V + 1);
    std::bitset<V_MAX> inQueue;
    int res = 0;
    
    for (int idx = 1; idx <= 2; ++idx) {
        
        std::fill(prev.begin(), prev.end(), 0);
        std::fill(costSum.begin(), costSum.end(), INF);
        inQueue.reset();
        
        std::queue<int> q;
        q.push(1);
        prev[1] = 1;
        costSum[1] = 0;
        inQueue[1] = true;
        
        for (int cursor; !q.empty(); ) {
            
            cursor = q.front();
            q.pop();
            inQueue[cursor] = false;
            
            for (const int& next : adjL[cursor]) {
                
                if (flow[cursor][next] < capa[cursor][next] && costSum[next] > costSum[cursor] + cost[cursor][next]) {
                    
                    costSum[next] = costSum[cursor] + cost[cursor][next];
                    prev[next] = cursor;
                    
                    if (!inQueue[next]) {
                        
                        q.push(next);
                        inQueue[next] = true;
                    }
                }
            }
        }
        
        for (int cursor = 2 * V; cursor != 1; cursor = prev[cursor]) {
            
            flow[prev[cursor]][cursor]++;
            flow[cursor][prev[cursor]]--;
            res += cost[prev[cursor]][cursor];
        }
    }
    
    std::cout << res << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    
    while (get_input()) {
        
        solve();
    }
    
    return 0;
}

