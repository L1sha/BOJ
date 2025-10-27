#include "bits/stdc++.h"

constexpr int N_MAX = 101, M_MAX = 10001, D_MAX = 1001;

const int INF = 1e9;

int N, M, K;

struct Adj {
    
    int to, cost, dist;
};

std::array<std::vector<Adj>, N_MAX> adjL;
std::array<std::array<int, M_MAX>, N_MAX> dp;
std::array<std::array<bool, M_MAX>, N_MAX> inQ;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> K;
    
    for (int airport = 1; airport <= N; ++airport) {
        
        adjL[airport].clear();
        
        for (int cost = 0; cost <= M; ++cost) {
            
            dp[airport][cost] = INF;
            inQ[airport][cost] = false;
        }
    }
    
    int from, to, cost, dist;
    
    while (K--) {
        
        std::cin >> from >> to >> cost >> dist;
        
        adjL[from].push_back({to, cost, dist});
    }
}

void solve() {
    
    std::queue<Adj> q;
    q.push({1, 0, 0});
    for (int cost = 0; cost <= M; ++cost) dp[1][cost] = 0;
    inQ[1][0] = 0;
    #include "bits/stdc++.h"

constexpr int N_MAX = 101, M_MAX = 10001, D_MAX = 1001;

const int INF = 1e9;

int N, M, K;

struct Adj {
    
    int to, cost, dist;
};

std::array<std::vector<Adj>, N_MAX> adjL;
std::array<std::array<int, M_MAX>, N_MAX> dp;
std::array<std::array<bool, M_MAX>, N_MAX> inQ;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> K;
    
    for (int airport = 1; airport <= N; ++airport) {
        
        adjL[airport].clear();
        
        for (int cost = 0; cost <= M; ++cost) {
            
            dp[airport][cost] = INF;
            inQ[airport][cost] = false;
        }
    }
    
    int from, to, cost, dist;
    
    while (K--) {
        
        std::cin >> from >> to >> cost >> dist;
        
        adjL[from].push_back({to, cost, dist});
    }
}

void solve() {
    
    std::queue<Adj> q;
    q.push({1, 0, 0});
    for (int cost = 0; cost <= M; ++cost) dp[1][cost] = 0;
    inQ[1][0] = 0;
    
    while (!q.empty()) {
        
        auto [cursor, cCost, cDist] = q.front();
        cDist = dp[cursor][cCost];
        q.pop();
        inQ[cursor][cCost] = false;
        
        if (cursor == N) continue;
        
        for (const auto& [next, nCost, nDist] : adjL[cursor]) {
            
            if (cCost + nCost <= M && dp[next][cCost + nCost] > cDist + nDist) {
                
                for (int cost = cCost + nCost; cost <= M; ++cost) {
                    
                    if (dp[next][cost] > cDist + nDist) dp[next][cost] = cDist + nDist;
                    else break;
                }
                
                if (!inQ[next][cCost + nCost]) {
                    
                    inQ[next][cCost + nCost] = true;
                    q.push({next, cCost + nCost, cDist + nDist});
                }
            }
        }
    }
    
    int res = INF;
    
    for (int cost = 0; cost <= M; ++cost) {
        
        res = std::min(res, dp[N][cost]);
    }
    
    if (res == INF) std::cout << "Poor KCM\n";
    else std::cout << res << '\n';
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


    while (!q.empty()) {
        
        auto [cursor, cCost, cDist] = q.front();
        cDist = dp[cursor][cCost];
        q.pop();
        inQ[cursor][cCost] = false;
        
        if (cursor == N) continue;
        
        for (const auto& [next, nCost, nDist] : adjL[cursor]) {
            
            if (cCost + nCost <= M && dp[next][cCost + nCost] > cDist + nDist) {
                
                for (int cost = cCost + nCost; cost <= M; ++cost) {
                    
                    if (dp[next][cost] > cDist + nDist) dp[next][cost] = cDist + nDist;
                    else break;
                }
                
                if (!inQ[next][cCost + nCost]) {
                    
                    inQ[next][cCost + nCost] = true;
                    q.push({next, cCost + nCost, cDist + nDist});
                }
            }
        }
    }
    
    int res = INF;
    
    for (int cost = 0; cost <= M; ++cost) {
        
        res = std::min(res, dp[N][cost]);
    }
    
    if (res == INF) std::cout << "Poor KCM\n";
    else std::cout << res << '\n';
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

