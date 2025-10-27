#include "bits/stdc++.h"

constexpr int N_MAX = 100;

int T, N;

std::array<std::pair<int, int>, N_MAX + 2> pts;
std::array<std::vector<int>, N_MAX + 2> adjL;
std::bitset<N_MAX> visited;




void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

int dist(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

void get_input() {
    
    std::cin >> N;
    
    for (int idx = 0; idx <= N + 1; ++idx) {
        
        std::cin >> pts[idx].first >> pts[idx].second;
        adjL[idx].clear();
    }
    
    for (int from = 0; from <= N + 1; ++from) {
        
        for (int to = from + 1; to <= N + 1; ++to) {
            
            if (dist(pts[from], pts[to]) <= 1000) {
                
                adjL[from].push_back(to);
                adjL[to].push_back(from);
            }
        }
    } 
}

bool isAbleToGo() {
    
    std::queue<int> q;
    std::vector<bool> visited(N + 2);
    
    q.push(0);
    visited[0] = true;
    
    for (int cursor; !q.empty(); ) {
        
        cursor = q.front();
        q.pop();
        
        for (const int& next : adjL[cursor]) {
            
            if (!visited[next]) {
                
                if (next == N + 1) return true;
                
                visited[next] = true;
                q.push(next);
            }
        }
    }
    
    return false;
}

void solve() {
    
    std::cin >> T;
    
    while (T--) {
        
        get_input();
        
        if (isAbleToGo()) std::cout << "happy\n";
        else std::cout << "sad\n";
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    solve();
    
    return 0;
}

