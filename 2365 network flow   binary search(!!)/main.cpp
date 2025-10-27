#include "bits/stdc++.h"

constexpr int N_MAX = 50;

const int INF = 1e9;

int N, targetFlow;

std::array<int, N_MAX> rowSum, colSum;
std::array<std::vector<int>, N_MAX * 2 + 2> adjL;
std::array<std::array<int, N_MAX * 2 + 2>, N_MAX * 2 + 2> capa, flow;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int row = 0; row < N; ++row) std::cin >> rowSum[row];
        
    for (int col = 0; col < N; ++col) std::cin >> colSum[col];
}

void resetFlow() {
    
    int source = N * 2, sink = N * 2  + 1;
    
    for (int idx = 0; idx < N; ++idx) {
        
        flow[source][idx] = 0;
        
        for (int idx2 = 0; idx2 < N; ++idx2) {
            
            flow[idx][N + idx2] = 0;
            flow[N + idx2][idx] = 0;
        }
        
        flow[N + idx][sink] = 0;
    }
}

bool check(const int& limit) {
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < N; ++col) { 
            
            capa[row][N + col] = limit;
        }
    }
    
    resetFlow();
    
    int totalFlow = 0, source = N * 2, sink = N * 2 + 1;
    std::vector<int> prev(N * 2 + 2);
    
    while (true) {
        
        std::fill(prev.begin(), prev.end(), -1);
        
        std::queue<int> q;
        q.push(source);
        prev[source] = source;
        
        for (int isDone = 0, cursor; !q.empty(); ) {
            
            cursor = q.front();
            q.pop();
            
            for (const int& next : adjL[cursor]) {
                
                if (prev[next] == -1 && flow[cursor][next] < capa[cursor][next]) {
                    
                    prev[next] = cursor;
                    q.push(next);
                    
                    if (next == sink) {
                        
                        isDone = 1;
                        break;
                    }
                }
            }
                
            if (isDone) break;
        }
        
        if (prev[sink] == -1) break;
        
        int newFlow = INF;
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            newFlow = std::min(newFlow, capa[prev[cursor]][cursor] - flow[prev[cursor]][cursor]);
        }
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            flow[prev[cursor]][cursor] += newFlow;
            flow[cursor][prev[cursor]] -= newFlow;
        }
        
        totalFlow += newFlow;
    }
    
    return totalFlow == targetFlow;
}

void solve() {
    
    int source = N * 2, sink = N * 2 + 1;
    
    for (int idx = 0; idx < N; ++idx) {
        
        targetFlow += rowSum[idx];
        
        adjL[source].push_back(idx);
        capa[source][idx] = rowSum[idx];
        
        for (int idx2 = 0; idx2 < N; ++idx2) {
            
            adjL[idx].push_back(N + idx2);
            adjL[N + idx2].push_back(idx);
        }
        
        adjL[N + idx].push_back(sink);
        capa[N + idx][sink] = colSum[idx];
    }
    
    int l = -1, r = 10'000, mid;
    
    while (r - l > 1) {
        
        mid = (l + r) / 2;
        
        if (check(mid)) r = mid;
        else l = mid;
    }
    
    if (mid != r) check(r);
    
    std::cout << r << '\n';
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < N; ++col) {
            
            std::cout << flow[row][N + col] << ' ';
        }
        
        std::cout << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

