#include "bits/stdc++.h"

constexpr int N_MAX = 50, M_MAX = 50;

const int INF = 1e9;

int N, M;

std::array<std::array<int, M_MAX>, N_MAX> map;
std::array<std::vector<int>, N_MAX * M_MAX + 2> adjL;
std::array<std::array<int, N_MAX * M_MAX + 2>, N_MAX * M_MAX + 2> capa, flow;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            std::cin >> map[row][col];
        }
    }
}

void solve() {
    
    int source = N * M, sink = N * M + 1;
    
    for (int idx = 0; idx < N * M + 2; ++idx) adjL[idx].clear();
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            if ((row + col) % 2 == 0) {
                
                adjL[source].push_back(row * M + col);
                capa[source][row * M + col] = map[row][col];
                flow[source][row * M + col] = 0;
                adjL[row * M + col].push_back(source);
                capa[row * M + col][source] = 0;
                flow[row * M + col][source] = 0;
            }
            else {
                
                adjL[row * M + col].push_back(sink);
                capa[row * M + col][sink] = map[row][col];
                flow[row * M + col][sink] = 0;
                adjL[sink].push_back(row * M + col);
                capa[sink][row * M + col] = 0;
                flow[sink][row * M + col] = 0;
                
                if (row != 0) {
                    
                    adjL[(row - 1) * M + col].push_back(row * M + col);
                    capa[(row - 1) * M + col][row * M + col] = INF;
                    flow[(row - 1) * M + col][row * M + col] = 0;
                    adjL[row * M + col].push_back((row - 1) * M + col);
                    capa[row * M + col][(row - 1) * M + col] = 0;
                    flow[row * M + col][(row - 1) * M + col] = 0;
                }
                
                if (row != N - 1) {
                    
                    adjL[(row + 1) * M + col].push_back(row * M + col);
                    capa[(row + 1) * M + col][row * M + col] = INF;
                    flow[(row + 1) * M + col][row * M + col] = 0;
                    adjL[row * M + col].push_back((row + 1) * M + col);
                    capa[row * M + col][(row + 1) * M + col] = 0;
                    flow[row * M + col][(row + 1) * M + col] = 0;
                }
                
                if (col != 0) {
                    
                    adjL[row * M + col - 1].push_back(row * M + col);
                    capa[row * M + col - 1][row * M + col] = INF;
                    flow[row * M + col - 1][row * M + col] = 0;
                    adjL[row * M + col].push_back(row * M + col - 1);
                    capa[row * M + col][row * M + col - 1] = 0;
                    flow[row * M + col][row * M + col - 1] = 0;
                }
                
                if (col != M - 1) {
                    
                    adjL[row * M + col + 1].push_back(row * M + col);
                    capa[row * M + col + 1][row * M + col] = INF;
                    flow[row * M + col + 1][row * M + col] = 0;
                    adjL[row * M + col].push_back(row * M + col + 1);
                    capa[row * M + col][row * M + col + 1] = 0;
                    flow[row * M + col][row * M + col + 1] = 0;
                }
            }
        }
    }
    
    int totalFlow = 0;
    std::vector<int> prev(N * M + 2);
    
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
        
        int newFlow = INT_MAX;
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            newFlow = std::min(newFlow, capa[prev[cursor]][cursor] - flow[prev[cursor]][cursor]);
        }
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            flow[prev[cursor]][cursor] += newFlow;
            flow[cursor][prev[cursor]] -= newFlow;
        }
        
        totalFlow -= newFlow;
    }
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            totalFlow += map[row][col];
        }
    }
    
    std::cout << totalFlow << '\n';
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

