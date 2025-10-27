#include "bits/stdc++.h"

constexpr int N_MAX = 100, M_MAX = 100;

int N, M, source, sink;

std::array<std::vector<int>, N_MAX + M_MAX + 2> adjL;
std::array<std::array<int, N_MAX + M_MAX + 2>, N_MAX + M_MAX + 2> capa, flow;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    source = 0;
    sink = N + M + 1;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        adjL[source].push_back(idx);
        std::cin >> capa[source][idx];
    }
    
    for (int idx = 1; idx <= M; ++idx) {
        
        adjL[N + idx].push_back(sink);
        std::cin >> capa[N + idx][sink];
    }
    
    for (int bookstore = 1; bookstore <= M; ++bookstore) {
        
        for (int person = 1; person <= N; ++person) {
            
            adjL[person].push_back(N + bookstore);
            adjL[N + bookstore].push_back(person);
            std::cin >> capa[person][N + bookstore];
        }
    }
}

void solve() {
    
    int res = 0;
    std::vector<int> prev(N + M + 2);
    
    while (true) {
        
        std::fill(prev.begin(), prev.end(), -1);
        
        std::queue<int> q;
        q.push(source);
        
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
        
        int newFlow = 1e9;
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            newFlow = std::min(newFlow, capa[prev[cursor]][cursor] - flow[prev[cursor]][cursor]);
        }
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            flow[prev[cursor]][cursor] += newFlow;
            flow[cursor][prev[cursor]] -= newFlow;
        }
        
        res += newFlow;
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

