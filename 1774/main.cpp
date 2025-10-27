#include "bits/stdc++.h"



int N, M, cursor, a, b;
long double res;

std::array<std::tuple<long double, int, int>, 500000> edges;
std::array<std::pair<long double, long double>, 1000> gods;
std::array<int, 1000> parent;

int getParent(int idx) {
    
    if (idx != parent[idx]) return parent[idx] = getParent(parent[idx]);
    return idx;
}

void Union(int idx1, int idx2) {
    
    parent[getParent(idx2)] = getParent(idx1);
}

long double dist (int idx1, int idx2) {
    
    return std::sqrt(std::pow(gods[idx1].first - gods[idx2].first, 2) + std::pow(gods[idx1].second - gods[idx2].second, 2));
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cout << std::fixed;
    std::cout.precision(2);
    
    std::cin >> N >> M;
    
    if (N == 1) {
        
        std::cout << "0.00";
        return 0;
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        parent[idx] = idx;
        std::cin >> gods[idx].first >> gods[idx].second;
    }
    
    while (M--) {
        
        std::cin >> a >> b;
        Union(a - 1, b - 1);
    }
    
    for (int idx1 = 0; idx1 < N; ++idx1) for (int idx2 = idx1 + 1; idx2 < N; ++idx2) {
        
        edges[cursor++] = {dist(idx1, idx2), idx1, idx2};
    }
    
    std::sort(edges.begin(), edges.begin() + (N * (N - 1) / 2));
    
    for (int idx = 0; idx < N * (N - 1) / 2; ++idx) {
        
        const auto& [weight, c1, c2] = edges[idx];
        
        if (getParent(c1) == getParent(c2)) continue;
        
        res += weight;
        Union(c1, c2);
    } 
    
    std::cout << res;
    
    return 0;
}

