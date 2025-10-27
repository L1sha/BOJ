#include "bits/stdc++.h"


int N, M, A, B, W;
char C;
std::array<int, 100'001> parent;
std::array<int, 100'001> weight;

void clear() {
    
    for (int idx = 1; idx <= N; ++idx) {
        
        parent[idx] = idx;
        weight[idx] = 0;
    }
}

std::pair<int, int> getParent(int idx) {
    
    if (parent[idx] != idx) {
        
        auto res = getParent(parent[idx]);
        
        parent[idx] = res.first;
        weight[idx] += res.second;
        
        return {res.first, weight[idx]};
    }
    
    return {idx, 0};
}

void Union(int idx1, int idx2, int diff) {
    
    auto p1 = getParent(idx1), p2 = getParent(idx2);
    
    parent[p2.first] = p1.first;
    weight[p2.first] = diff + p1.second - p2.second;
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    while (std::cin >> N >> M) {
        
        clear();
        
        while (M--) {
            
            std::cin >> C;
            
            switch (C) {
                
                case '!' :
                
                std::cin >> A >> B >> W;
                
                Union(A, B, W);
                
                break;
                
                case '?' :
                
                std::cin >> A >> B;
                
                auto p1 = getParent(A), p2 = getParent(B);
                
                if (p1.first == p2.first) {
                    
                    std::cout << p2.second - p1.second << '\n';
                }
                else {
                    
                    std::cout << "UNKNOWN\n";
                }
                
                break;
            }
        }
    }
    
    return 0;
}

