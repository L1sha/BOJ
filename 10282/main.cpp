#include "bits/stdc++.h"

constexpr int N_MAX = 10'001, INF = 1e9;

std::vector<std::vector<std::pair<int, int>>> adjL;

int T, N, D, C;

std::queue<int> q;
std::bitset<N_MAX> inQueue;
std::array<int, N_MAX> distArr;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> D >> C;
    
    adjL.clear();
    adjL.resize(N + 1);
    std::fill(distArr.begin() + 1, distArr.begin() + N + 1, INF);
    inQueue.reset();
    
    for (int from, to, dist; D--; ) {
        
        std::cin >> to >> from >> dist;
        adjL[from].push_back({to, dist});
    }
}

void solve() {
    
    q.push(C);
    inQueue[C] = true;
    distArr[C] = 0;
    
    while (!q.empty()) {
        
        auto cursor = q.front();
        q.pop();
        inQueue[cursor] = false;
        
        for (const auto& [next, nextDist] : adjL[cursor]) {
            
            if (distArr[cursor] + nextDist < distArr[next]) {
                
                if (!inQueue[next]) {
                    
                    q.push(next);
                    inQueue[next] = true;
                }
                
                distArr[next] = distArr[cursor] + nextDist;
            }
        }
    }
    
    int cnt = 0, max = 0;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (distArr[idx] != INF) {
            
            ++cnt;
            max = std::max(max, distArr[idx]);
        }
    }
    
    std::cout << cnt << ' ' << max << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    
    std::cin >> T;
    
    while (T--) {
        
        get_input();
        solve();
    }
    
    return 0;
}