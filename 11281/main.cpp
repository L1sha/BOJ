#include "bits/stdc++.h"


int N, M, I, J, cnt;
std::bitset<10'001> ans;
std::bitset<20'002> visited;
std::array<std::vector<int>, 20'002> condition, backCondition;
std::array<int, 20'002> finishedOrder;
std::array<int, 20'002> SCC;

int convert(int idx) {
    
    if (idx > 0) {
        
        return 10'001 + idx;
    }
    
    return -idx;
}

int convert(int idx, bool val) {
    
    if (val) {
        
        return 10'001 + idx;
    }
    
    return idx;
}

void DFS(int idx) {
    
    visited[idx] = true;
    
    for (const int& next : condition[idx]) {
        
        if (!visited[next]) {
            
            DFS(next);
        }
    }
    
    finishedOrder[++cnt] = idx;
}

void backDFS(int idx) {
    
    SCC[idx] = cnt;
    
    for (const int& next : backCondition[idx]) {
        
        if (!SCC[next]) {
            
            backDFS(next);
        }
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> I >> J;
        
        if (I != -J) {
            
            condition[convert(-I)].push_back(convert(J));
            condition[convert(-J)].push_back(convert(I));
            
            backCondition[convert(J)].push_back(convert(-I));
            backCondition[convert(I)].push_back(convert(-J));
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (!visited[convert(idx, true)]) {
            
            DFS(convert(idx, true));
        }
        
        if (!visited[convert(idx, false)]) {
            
            DFS(convert(idx, false));
        }
    }
    
    cnt = 0;
    
    for (int idx = 2 * N; idx >= 1; --idx) {
        
        if (!SCC[finishedOrder[idx]]) {
            
            cnt++;
            
            backDFS(finishedOrder[idx]);
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (SCC[convert(idx, true)] == SCC[convert(idx, false)]) {
            
            std::cout << 0;
            
            return 0;
        }
        
        if (SCC[convert(idx, true)] > SCC[convert(idx, false)]) {
            
            ans[idx] = true;
        }
    }
    
    std::cout << 1 << '\n';
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cout << ans[idx] << ' ';
    }
    
    return 0;
}

