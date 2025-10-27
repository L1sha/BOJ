#include "bits/stdc++.h"

constexpr int N_MAX = 400, M_MAX = 400;

const int INF = 1e9;

int N, M, source, sink;

std::array<std::vector<int>, N_MAX + M_MAX + 2> adjL;
std::array<std::array<int, M_MAX>, N_MAX> cost;
std::array<std::bitset<N_MAX + M_MAX + 2>, N_MAX + M_MAX + 2> flowable;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    source = 0, sink = N + M + 1;
    
    for (int employee = 1, workCnt, workNum, pay; employee <= N; ++employee) {
        
        std::cin >> workCnt;
        
        while (workCnt--) {
            
            std::cin >> workNum >> pay;
            
            adjL[employee].push_back(N + workNum);
            flowable[employee][N + workNum] = true;
            
            adjL[N + workNum].push_back(employee);
            
            cost[employee - 1][workNum - 1] = pay;
        }
    }
    
    for (int employee = 1; employee <= N; ++employee) {
        
        adjL[source].push_back(employee);
        flowable[source][employee] = true;
    }
    
    for (int work = 1; work <= M; ++work) {
        
        adjL[N + work].push_back(sink);
        flowable[N + work][sink] = true;
    }
}

void solve() {
    
    int totalFlow = 0, totalCost = 0;
    
    std::vector<int> dist(N + M + 2), prev(N + M + 2);
    std::vector<bool> inQueue(N + M + 2);
    
    while (true) {
        
        std::fill(dist.begin(), dist.end(), INF);
        std::fill(prev.begin(), prev.end(), -1);
        
        std::queue<int> q;
        q.push(source);
        dist[source] = 0;
        inQueue[source] = true;
        
        for (int cursor, costAdd; !q.empty(); ) {
            
            cursor = q.front();
            q.pop();
            inQueue[cursor] = false;
            
            for (const int& next : adjL[cursor]) {
                
                if (cursor == source || next == sink) costAdd = 0;
                else if (cursor <= N) costAdd = -cost[cursor - 1][next - N - 1];
                else costAdd = cost[next - 1][cursor - N - 1];
                
                if (dist[cursor] + costAdd < dist[next] && flowable[cursor][next]) {
                    
                    dist[next] = dist[cursor] + costAdd;
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
            
            flowable[prev[cursor]][cursor] = false;
            flowable[cursor][prev[cursor]] = true;
        }
        
        totalFlow++;
        totalCost -= dist[sink];
    }
    
    std::cout << totalFlow << '\n' << totalCost;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

