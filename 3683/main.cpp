#include "bits/stdc++.h"

constexpr int V_MAX = 500;

int C, D, V, N, M;

std::array<std::pair<int, int>, V_MAX> catLover, dogLover;
std::array<std::vector<int>, V_MAX> adjL;
std::array<int, V_MAX> occupied;
std::bitset<V_MAX> visited;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> C >> D >> V;
    N = 0;
    M = 0;
    
    char c;
    
    for (int num, idx = 0; idx < V; ++idx) {
        
        std::cin >> c >> num;
        
        if (c == 'C') {
            
            catLover[N].first = num;
            std::cin >> c >> num;
            catLover[N++].second = num;
        }
        else {
            
            dogLover[M].first = num;
            std::cin >> c >> num;
            dogLover[M++].second = num;
        }
    }
    
    for (int cat = 0; cat < N; cat++) {
        
        for (int dog = 0; dog < M; dog++) {
            
            if (catLover[cat].first == dogLover[dog].second || catLover[cat].second == dogLover[dog].first) {
                
                adjL[cat].push_back(dog);
            }
        }
    }
}

int DFS(int cursor) {
    
    for (const int& next : adjL[cursor]) {
        
        if (!visited[next]) {
            
            visited[next] = true;
            
            if (occupied[next] == -1 || DFS(occupied[next])) {
                
                occupied[next] = cursor;
                return 1;
            }
        }
    }
    
    return 0;
}

void solve() {
    
    int T, res;
    std::cin >> T;
    
    while (T--) {
        
        get_input();
        
        res = 0;
        std::fill(occupied.begin(), occupied.begin() + M, -1);
        
        for (int cat = 0; cat < N; ++cat) {
            
            visited.reset();
            res += DFS(cat);
        }
        
        std::cout << V - res << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    solve();
    
    return 0;
}

