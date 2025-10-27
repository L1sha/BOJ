#include "bits/stdc++.h"

constexpr int N_MAX = 10'000;

int N;

std::vector<std::vector<int>> adjL;
std::vector<int> level, A, B;

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    adjL.clear();
    adjL.resize(N + 1);
    
    level.clear();
    level.resize(N + 1);
    
    A.clear();
    A.resize(N + 1, N);
    
    B.clear();
    B.resize(N, N);
    
    std::string noUse;
    char noUse2;
    int length, input;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> noUse >> noUse2 >> length >> noUse2;
        while (length--) {
            
            std::cin >> input;
            adjL[idx].push_back(input - N);
        }
    }
}

bool BFS() {
    
    std::queue<int> q;
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (A[idx] == N) {
            
            level[idx] = 0;
            q.push(idx);
        }
        else level[idx] = -1;
    }
    level[N] = -1;
    
    for (int curr; !q.empty(); ) {
        
        curr = q.front();
        q.pop();
        
        for (const auto& next : adjL[curr]) {
            
            if (level[B[next]] == -1) {
                
                level[B[next]] = level[curr] + 1;
                q.push(B[next]);
            }
        }
    }
    
    return level[N] != -1;
}

bool DFS(int curr) {
    
    for (const auto& next : adjL[curr]) {
        
        if (level[B[next]] == level[curr] + 1 && (B[next] == N || DFS(B[next]))) {
            
            A[curr] = next;
            B[next] = curr;
            
            return true;
        }
    }
    
    level[curr] = -1;
    return false;
}

void solve() {
    
    int res = 0;
    
    while (BFS()) {
        
        for (int idx = 0; idx < N; ++idx) {
            
            if (level[idx] == 0 && DFS(idx)) ++res;
        }
    }
    
    std::cout << res << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    while (std::cin >> N) {
        
        get_input();
        solve();
    }
    
    return 0;
}