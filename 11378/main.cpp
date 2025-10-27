#include "bits/stdc++.h"

constexpr int N_MAX = 1001, M_MAX = 1001;

int N, M, K;

std::array<std::vector<int>, N_MAX + M_MAX> adjL;
std::array<std::array<int, N_MAX + M_MAX>, N_MAX + M_MAX> capa, flow;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> K;
    
    for (int idx = 1, workNum, work; idx <= N; ++idx) {
        
        std::cin >> workNum;
        
        while (workNum--) {
            
            std::cin >> work;
            
            adjL[idx].push_back(N + work);
            capa[idx][N + work] = 1;
            adjL[N + work].push_back(idx);
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

int BFS(int source = 0, int sink = N + M + 1) {
    
    std::vector<int> prev(N + M + 2);
    int res = 0, cnt = 0;
    bool sw = false;
    
    while (true) {
        
        std::fill(prev.begin(), prev.end(), -1);
        
        std::queue<int> q;
        q.push(source);
        prev[source] = source;
        
        for (int cursor; !q.empty();) {
            
            cursor = q.front();
            q.pop();
            
            if (cursor == sink) break;
            
            for (const int& next : adjL[cursor]) {
                
                if (prev[next] == -1 && flow[cursor][next] < capa[cursor][next]) {
                    
                    prev[next] = cursor;
                    q.push(next);
                }
            }
        }
        
        if (prev[sink] != -1) {
            
            for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
                
                flow[prev[cursor]][cursor]++;
                flow[cursor][prev[cursor]]--;
            }
            
            res++;
            
            if (sw) cnt++;
        }
        
        if (prev[sink] == -1 || cnt == K) {
            
            if (sw) break;
            sw = true;
            for (int idx = 1; idx <= N; ++idx) capa[0][idx] = K + 1;
        }
        

    }
    
    return res;
}

void solve() {
    
    std::cout << BFS();
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

