#include "bits/stdc++.h"


using road = std::pair<int, std::pair<int, int>>;

int N, M;

std::array<int, 100'001> parent;
std::array<road, 1'000'001> roads;

int getParent(int idx){
    
    if (parent[idx] != idx) return parent[idx] = getParent(parent[idx]);
    return idx;
}

void Union(int idx1, int idx2) {
    
    parent[getParent(idx2)] = getParent(idx1);
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    int A, B, C;
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> A >> B >> C;
        roads[idx] = {C, {A, B}};
    }
    
    std::sort(roads.begin(), roads.begin() + M);
    
    for (int idx = 1; idx <= N; ++idx) parent[idx] = idx;
    
    int res = 0, cnt = 0;
    
    for (auto& road : roads) {
        
        if (cnt == N - 2) break;
        
        C = road.first;
        A = road.second.first;
        B = road.second.second;
        
        if (getParent(A) == getParent(B)) continue;
        
        Union(A, B);
        res += C;
        cnt++;
    }
    
    std::cout << res;
    
    return 0;
}


