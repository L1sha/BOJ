#include "bits/stdc++.h"

constexpr int N_MAX = 1001, M_MAX = 1001;

int N, M, K;

std::array<std::vector<int>, N_MAX> adjL;
std::bitset<M_MAX> visited;
std::array<int, M_MAX> occupied;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> K;
    
    for (int idx = 1, workNum, work; idx <= N; ++idx) {
        
        std::cin >> workNum;
        while (workNum--) {
            
            std::cin >> work;
            adjL[idx].push_back(work);
        }
    }
}

int DFS(int cursor) {
    
    for (const int& work : adjL[cursor]) {
        
        if (!visited[work] && occupied[work] != cursor) {
            
            visited[work] = true;
            
            if (occupied[work] == 0 || DFS(occupied[work])) {
                
                occupied[work] = cursor;
                return 1;
            }
        }
    }
    
    return 0;
}

void solve() {
    
    int res = 0;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        visited.reset();
        
        res += DFS(idx);
    }
    
    for (int idx = 1, cnt = 0; idx <= N; ++idx) {
        
        visited.reset();
        
        if (DFS(idx)) {
            
            res++;
            if (++cnt == K) break;
            idx--;
        }
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

