#include "bits/stdc++.h"



int N, cnt = 1, cursor;
long double res;

std::array<std::tuple<long double, int, int>, 4950> edges;
std::array<std::pair<long double, long double>, 100> stars;
std::array<int, 100> parent;

int getParent(int idx) {
    
    if (idx != parent[idx]) return parent[idx] = getParent(parent[idx]);
    return idx;
}

void Union(int idx1, int idx2) {
    
    parent[getParent(idx2)] = getParent(idx1);
}

long double dist (int idx1, int idx2) {
    
    return std::sqrt(std::pow(stars[idx1].first - stars[idx2].first, 2) + std::pow(stars[idx1].second - stars[idx2].second, 2));
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    if (N == 1) {
        
        std::cout << 0;
        return 0;
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        parent[idx] = idx;
        std::cin >> stars[idx].first >> stars[idx].second;
    }
    
    for (int idx1 = 0; idx1 < N; ++idx1) for (int idx2 = idx1 + 1; idx2 < N; ++idx2) {
        
        edges[cursor++] = {dist(idx1, idx2), idx1, idx2};
    }
    
    std::sort(edges.begin(), edges.begin() + (N * (N - 1) / 2));
    cursor = 0;
    
    while (true) {
        
        const auto& [weight, c1, c2] = edges[cursor++];
        
        if (getParent(c1) == getParent(c2)) continue;
        
        res += weight;
        Union(c1, c2);
        if (++cnt == N) break;
    } 
    
    std::cout << res;
    
    return 0;
}

