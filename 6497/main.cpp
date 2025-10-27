#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int M, N, x, y, z, res, cnt;

std::array<std::tuple<int, int, int>, 200'000> edges;
std::array<int, 200'000> parent;

int getParent(int idx) {
    
    if (idx != parent[idx]) return parent[idx] = getParent(parent[idx]);
    return idx;
}

void Union(int idx1, int idx2) {
    
    parent[getParent(idx2)] = getParent(idx1);
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    while (true) {

        std::cin >> M >> N;
        
        if (!M && !N) break;
        
        res = 0;
        cnt = 1;
        for (int idx = 0; idx < M; ++idx) parent[idx] = idx;
        
        for (int idx = 0; idx < N; ++idx) {
            
            std::cin >> x >> y >> z;
            
            edges[idx] = {z, x, y};
            res += z;
        }
        
        std::sort(edges.begin(), edges.begin() + N);
        
        for (int idx = 0; idx < N; ++idx) {
            
            const auto& [weight, c1, c2] = edges[idx];
            
            if (getParent(c1) == getParent(c2)) continue;
            
            res -= weight;
            Union(c1, c2);
            if (++cnt == M) break;
        }
        
        std::cout << res << '\n';
    }    
    
    return 0;
}

