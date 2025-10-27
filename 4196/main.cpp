#include "bits/stdc++.h"


constexpr int N_MAX = 100'001;

int T, N, M, X, Y, cnt;

std::bitset<N_MAX> done;
std::array<int, N_MAX> visited;
std::array<std::vector<int>, N_MAX> adjL;
std::vector<std::vector<int>> SCCs;
std::stack<int> stk;

void init() {
    
    for (int idx = 1; idx <= N; ++idx) {
        
        adjL[idx].clear();
        visited[idx] = 0;
    }
    SCCs.clear();
    done.reset();
    cnt = 0;
}

int makeSCC(int cursor) {
    
    int leastDest = visited[cursor] = ++cnt;
    stk.push(cursor);
    
    for (const int& next : adjL[cursor]) {
        
        if (visited[next]) {
            
            if (!done[next]) {
                
                leastDest = std::min(leastDest, visited[next]);
            }
        }
        else {
            
            leastDest = std::min(leastDest, makeSCC(next));
        }
    }
    
    if (leastDest == visited[cursor]) {
        
        std::vector<int> newSCC;
        
        while (stk.top() != cursor) {
            
            newSCC.push_back(stk.top());
            done[stk.top()] = true;
            stk.pop();
        }
        
        newSCC.push_back(cursor);
        done[cursor] = true;
        stk.pop();
        
        SCCs.push_back(std::move(newSCC));
    }
    
    return leastDest;
}

void DFS(int cursor) {
    
    done[cursor] = true;
    
    for (const int& next : adjL[cursor]) {
        
        if (!done[next]) {
            
            DFS(next);
        }
    }
}

void solve() {
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (!done[idx]) {
            
            makeSCC(idx);
        }
    }
    
    cnt = 0;
    done.reset();
    
    for (auto it = SCCs.rbegin(); it != SCCs.rend(); ++it) {
        
        if (!done[(*it).front()]) {
            
            cnt++;
            DFS((*it).front());
        }
    }
    
    std::cout << cnt << '\n';
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> N >> M;
        
        init();
        
        while (M--) {
            
            std::cin >> X >> Y;
            
            adjL[X].push_back(Y);
        }
        
        solve();
    }
    
    return 0;
}

