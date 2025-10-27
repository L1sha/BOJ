#include "bits/stdc++.h"

constexpr int N_MAX = 1000, M_MAX = 5000;

int N, M;

std::array<int, N_MAX + 1> parent;
std::array<std::vector<int>, N_MAX + 1> adjL;
std::bitset<N_MAX + 1> visited;

int getParent(int curr) {
    
    if (parent[curr] == curr) return curr;
    return parent[curr] = getParent(parent[curr]);
}

void doUnion(int left, int right) {
    
    parent[getParent(right)] = getParent(left);
}



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
}

void DFS(int curr, std::vector<int>& even, std::vector<int>& odd, int height = 0) {
    
    visited[curr] = true;
    if (height & 1) odd.push_back(curr);
    else even.push_back(curr);
    
    for (const auto& next : adjL[curr]) {
        
        if (!visited[next]) DFS(next, even, odd, height + 1);
    }
}

void solve() {
    
    std::iota(parent.begin(), parent.begin() + N + 1, 0);
    
    char c;
    int p, q;
    
    while (M--) {
        
        std::cin >> c >> p >> q;
        
        if (c == 'E') {
            
            adjL[p].push_back(q);
            adjL[q].push_back(p);
        }
        else {
            
            doUnion(p, q);
        }
    }
    
    for (int curr = 1; curr <= N; ++curr) {
        
        if (!visited[curr]) {
            
            std::vector<int> even, odd;
            
            DFS(curr, even, odd);
            
            for (int idx = 1; idx < even.size(); ++idx) {
                
                doUnion(even[0], even[idx]);
            }
            
            for (int idx = 1; idx < odd.size(); ++idx) {
                
                doUnion(odd[0], odd[idx]);
            }
        }
    }
    
    int res = 0;
    
    for (int curr = 1; curr <= N; ++curr) {
        
        if (parent[curr] == curr) ++res;
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}