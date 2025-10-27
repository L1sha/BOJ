#include "bits/stdc++.h"


constexpr int N_MAX = 500'001;

int N, M, from, to, S, P, cnt;

std::bitset<N_MAX> hasRestaurant;
std::bitset<N_MAX> done;
std::array<int, N_MAX> visited;
std::array<int, N_MAX> mySCC;
std::array<int, N_MAX> cash;
std::array<std::vector<int>, N_MAX> adjL;
std::bitset<N_MAX> hasRestaurant_SCC;
std::array<int, N_MAX> cash_SCC;
std::array<std::vector<int>, N_MAX> adjL_SCC;
std::array<int, N_MAX> memo_SCC;
std::vector<std::vector<int>> SCCs;
std::stack<int> stk;

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
        int sz = SCCs.size(), top;
        
        while ((top = stk.top()) != cursor) {
            
            done[top] = true;
            mySCC[top] = sz;
            if (hasRestaurant[top]) { hasRestaurant_SCC[sz] = true; }
            cash_SCC[sz] += cash[top];
            newSCC.push_back(top);
            stk.pop();
        }
        
        done[cursor] = true;
        mySCC[cursor] = sz;
        if (hasRestaurant[cursor]) { hasRestaurant_SCC[sz] = true; }
        cash_SCC[sz] += cash[cursor];
        newSCC.push_back(cursor);
        stk.pop();
        
        SCCs.push_back(std::move(newSCC));
    }
    
    return leastDest;
}

void makeSCC() {
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (!done[idx]) {
            
            DFS(idx);
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        for (const auto& next : adjL[idx]) {
            
            if (mySCC[idx] == mySCC[next]) {
                
                continue;
            }
            
            adjL_SCC[mySCC[idx]].push_back(mySCC[next]);
        }
    }
    
    std::fill(memo_SCC.begin(), memo_SCC.begin() + SCCs.size(), -1);
}

int solve(int cursor_SCC) {
    
    if (memo_SCC[cursor_SCC] != -1) {
        
        return memo_SCC[cursor_SCC];
    }
    
    int max = cash_SCC[cursor_SCC], temp;
    bool hasAnswer = hasRestaurant_SCC[cursor_SCC];
    
    for (const auto& next_SCC : adjL_SCC[cursor_SCC]) {
        
        temp = solve(next_SCC);
        
        if (temp != -1) {
            
            hasAnswer = true;
            max = std::max(max, cash_SCC[cursor_SCC] + temp);
        }
    }
    
    if (hasAnswer) {
        
        return memo_SCC[cursor_SCC] = max;
    }
    else {
        
        return memo_SCC[cursor_SCC] = -1;
    }
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    while (M--) {
        
        std::cin >> from >> to;
        
        adjL[from].push_back(to);
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> cash[idx];
    }
    
    std::cin >> S >> P;
    
    while (P--) {
        
        std::cin >> M;
        
        hasRestaurant[M] = true;
    }
    
    makeSCC();
    
    std::cout << solve(mySCC[S]);
    
    return 0;
}

