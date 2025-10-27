#include "bits/stdc++.h"

constexpr int N_MAX = 401;

int N, P;

std::array<std::array<int, N_MAX>, N_MAX> capa, flow;
std::array<std::vector<int>, N_MAX> adjL;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> P;
    
    for (int from, to; P--;) {
        
        std::cin >> from >> to;
        
        adjL[from].push_back(to);
        capa[from][to] = 1;
        
        adjL[to].push_back(from);
        capa[to][from] = 0;
    }
}

int BFS(int source = 1, int sink = 2) {
    
    int res = 0;
    std::vector<int> prev(N + 1);
    
    while (true) {
        
        std::fill(prev.begin(), prev.end(), 0);
        
        std::queue<int> q;
        q.push(source);
        prev[source] = source;
        
        for (int cursor; !q.empty();) {
            
            cursor = q.front();
            q.pop();
            
            if (cursor == sink) break;
            
            for (const int& next : adjL[cursor]) {
                
                if (!prev[next] && flow[cursor][next] < capa[cursor][next]) {
                    
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

