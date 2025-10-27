#include "bits/stdc++.h"


constexpr int N_MAX = 400;
const int INF = 1e9;

int N, P;

std::array<std::array<int, N_MAX * 2 + 1>, N_MAX * 2 + 1> flow, cap;
std::array<std::vector<int>, N_MAX * 2 + 1> adjL;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> P;
    
    for (int from, to; P--;) {
        
        std::cin >> from >> to;
        
        adjL[from].push_back(to + N);
        cap[from][to + N] = INF;
        
        adjL[to + N].push_back(from);
        cap[to + N][from] = 0;
        
        adjL[to].push_back(from + N);
        cap[to][from + N] = INF;
        
        adjL[from + N].push_back(to);
        cap[from + N][to] = 0;
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        adjL[idx].push_back(idx + N);
        cap[idx][idx + N] = 0;
        
        adjL[idx + N].push_back(idx);
        cap[idx + N][idx] = 1;
    }
}

int BFS(int source = 1, int sink = 2 + N) {
    
    int res = 0;
    std::vector<int> prev(2 * N + 1);
    
    while (true) { 
        
        std::queue<int> q;
        q.push(source);
        
        std::fill(prev.begin(), prev.end(), 0);
        prev[source] = source;
        
        for (int cursor; !q.empty();) {
            
            cursor = q.front();
            q.pop();
            
            if (cursor == sink) break;
            
            for (const int& next : adjL[cursor]) {
                
                if (flow[cursor][next] < cap[cursor][next] && !prev[next]) {
                    
                    prev[next] = cursor;
                    q.push(next);
                }
            }
        }
        
        if (!prev[sink]) break;
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            flow[prev[cursor]][cursor]++;
            flow[cursor][prev[cursor]]--;
        }
        
        res++;
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

