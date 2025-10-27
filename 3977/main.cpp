#include "bits/stdc++.h"


constexpr int N_MAX = 100'000;

int T, N, M, from, to, cnt;

std::bitset<N_MAX> done;
std::array<int, N_MAX> visited;
std::array<std::vector<int>, N_MAX> adjL;
std::vector<std::vector<int>> SCCs;
std::stack<int> stk;

void clear() {
    
    for (int idx = 0; idx < N; ++idx) {
        
        adjL[idx].clear();
        visited[idx] = 0;
    }
    
    cnt = 0;
    done.reset();
    SCCs.clear();
}

int DFS(int cursor) {
    
    int leastDest = visited[cursor] = ++cnt;
    stk.push(cursor);
    
    for (const int& next : adjL[cursor]) {
        
        if (visited[next]) {
            
            if (!done[next]) {
                
                leastDest = std::min(leastDest, visited[next]);
            }
        }
        else {
            
            leastDest = std::min(leastDest, DFS(next));
        }
    }
    
    if (leastDest == visited[cursor]) {
        
        std::vector<int> newSCC;
        
        while (cursor != stk.top()) {
            
            done[stk.top()] = true;
            newSCC.push_back(stk.top());
            stk.pop();
        }
        
        done[cursor] = true;
        newSCC.push_back(cursor);
        stk.pop();
        
        SCCs.push_back(std::move(newSCC));
    }
    
    return leastDest;
}

void makeSCC() {
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (!done[idx]) {
            
            DFS(idx);
        }
    }
}

void justDFS(int cursor) {
    
    done[cursor] = true;
    
    for (const int& next : adjL[cursor]) {
        
        if (!done[next]) {
            
            justDFS(next);
        }
    }
}

void solve() {
    
    done.reset();
    
    justDFS(SCCs.back().front());
    
    for (const auto& SCC : SCCs) {
        
        if (!done[SCC.front()]) {
            
            std::cout << "Confused\n\n";
            
            return;
        }
    }
    
    std::sort(SCCs.back().begin(), SCCs.back().end());
    
    for (const auto& el : SCCs.back()) {
        
        std::cout << el << '\n';
    }
    
    std::cout << '\n';
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> N >> M;
        
        clear();
        
        while (M--) {
            
            std::cin >> from >> to;
            
            adjL[from].push_back(to);
        }
        
        makeSCC();
        
        solve();
    }
    
    return 0;
}

