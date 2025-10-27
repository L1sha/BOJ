#include "bits/stdc++.h"


int T, N, from, to, root;
std::array<std::vector<int>, 10'001> child;
std::array<int, 10'001> parent;
std::array<int, 10'001> rank;

void DFS(int cursor, int height) {
    
    rank[cursor] = height;
    
    for (const int& next : child[cursor]) {
        
        DFS(next, height + 1);
    }
}

int solve(int A, int B) {
    
    if (rank[A] < rank[B]) {
        
        std::swap(A, B);
    }
    
    while (rank[A] > rank[B]) {
        
        A = parent[A];
    }
    
    while (A != B) {
        
        A = parent[A];
        B = parent[B];
    }
    
    return A;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> N;
        
        for (int idx = 1; idx <= N; ++idx) {
            
            child[idx].clear();
            parent[idx] = 0;
        }
        
        for (int idx = 1; idx < N; ++idx) {
            
            std::cin >> from >> to;
            child[from].push_back(to);
            parent[to] = from;
        }
        
        std::cin >> from >> to;
        
        for (int idx = 1; idx <= N; ++idx) {
            
            if (parent[idx] == 0) {
                
                root = idx;
                break;
            }
        }
        
        DFS(root, 0);
        
        std::cout << solve(from, to) << '\n';
    }
    
    return 0;
}

