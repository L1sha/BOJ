#include "bits/stdc++.h"

constexpr int N_MAX = 50, M_MAX = 50;

const int INF = 1e9;

std::array<std::array<int, 5>, 5> score;

int N, M, source, sink;

std::array<std::array<int, M_MAX>, N_MAX> tofu;
std::array<std::vector<int>, N_MAX * M_MAX + 2> adjL;
std::array<std::array<int, N_MAX * M_MAX + 2>, N_MAX * M_MAX + 2> cost;
std::array<std::bitset<N_MAX * M_MAX + 2>, N_MAX * M_MAX + 2> flowable;




void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    score[0] = {10, 8, 7, 5, 1};
    score[1] = {8, 6, 4, 3, 1};
    score[2] = {7, 4, 3, 2, 1};
    score[3] = {5, 3, 2, 2, 1};
    score[4] = {1, 1, 1, 1, 0};
    
    std::cin >> N >> M;
    
    char c;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
           std::cin >> c;
           
           tofu[row][col] = c - 'A';
           if (tofu[row][col] == 5) tofu[row][col] = 4;
        }
    }
}

void solve() {
    
    source = N * M;
    sink = N * M + 1;
    
    for (int cursor, row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            cursor = row * M + col;
            
            if ((row + col) % 2 == 0) {
                
                adjL[source].push_back(cursor);
                flowable[source][cursor] = true;
            }
            else {
                
                adjL[cursor].push_back(sink);
                flowable[cursor][sink] = true;
                
                std::vector<int> adjCells;
                
                if (row != 0) adjCells.push_back((row - 1) * M + col);
                if (row != N - 1) adjCells.push_back((row + 1) * M + col);
                if (col != 0) adjCells.push_back(row * M + col - 1);
                if (col != M - 1) adjCells.push_back(row * M + col + 1);
                
                for (int& adj : adjCells) {
                    
                    adjL[adj].push_back(cursor);
                    flowable[adj][cursor] = true;
                    cost[adj][cursor] = -score[tofu[adj / M][adj % M]][tofu[row][col]];
                    
                    adjL[cursor].push_back(adj);
                    cost[cursor][adj] = score[tofu[adj / M][adj % M]][tofu[row][col]];
                }
            }
        }
    }
    
    int totalCost = 0;
    
    std::queue<int> q;
    std::vector<int> dist(N * M + 2), prev(N * M + 2);
    std::vector<bool> inQueue(N * M + 2);
    
    while (true) {
        
        std::fill(dist.begin(), dist.end(), INF);
        std::fill(prev.begin(), prev.end(), -1);
        
        q.push(source);
        dist[source] = 0;
        
        for (int cursor; !q.empty(); ) {
            
            cursor = q.front();
            q.pop();
            inQueue[cursor] = false;
            
            for (const int& next : adjL[cursor]) {
                
                if (flowable[cursor][next] && dist[cursor] + cost[cursor][next] < dist[next]) {
                    
                    dist[next] = dist[cursor] + cost[cursor][next];
                    prev[next] = cursor;
                    
                    if (!inQueue[next]) {
                        
                        q.push(next);
                        inQueue[next] = true;
                    }
                }
            }
        }
        
        if (dist[sink] > 0) break;
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            flowable[prev[cursor]][cursor] = false;
            flowable[cursor][prev[cursor]] = true;
        }
        
        totalCost -= dist[sink];
    }
    
    std::cout << totalCost;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

