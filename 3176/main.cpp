#include "bits/stdc++.h"


using intPair = std::pair<int, int>;        
using minmax = std::tuple<int, int, int>;   // <parentIdx, min, max>

int N, A, B, C, K;
constexpr int MAX = std::ceil(log2(100'001));

std::array<std::vector<intPair>, 100'001> adjL;
std::array<std::array<minmax, MAX>, 100'001> parents;
std::array<int, 100'001> height;



void init(int cursor, int parent, int weight) {
    
    height[cursor] = height[parent] + 1;
    parents[cursor][0] = {parent, weight, weight};
    for (int idx = 1; idx < MAX; ++idx) {
        
        const auto& [p1, m1, M1] = parents[cursor][idx - 1];
        const auto& [p2, m2, M2] = parents[p1][idx - 1];
        
        if (p2 == 0) {
            
            break;
        }
        
        parents[cursor][idx] = {p2, std::min(m1, m2), std::max(M1, M2)};
    }
    
    for (auto& next : adjL[cursor]) {
        
        if (next.second == parent) {
            
            continue;
        }
        
        init(next.second, cursor, next.first);
    }
}

intPair LCA(int A, int B) {
    
    if (height[A] > height[B]) {
        
        std::swap(A, B);
    }
    
    int min = 1'000'001, max = 0;
    
    for (int idx = MAX - 1; idx >= 0; --idx) {
        
        const auto& [p, m, M] = parents[B][idx];
        
        if (height[p] >= height[A]) {
            
            B = p;
            min = std::min(min, m);
            max = std::max(max, M);
        }
    }
    
    if (A == B) {
        
        return {min, max};
    }
    
    for (int idx = MAX - 1; idx >= 0; --idx) {
        
        const auto& [p1, m1, M1] = parents[A][idx];
        const auto& [p2, m2, M2] = parents[B][idx];
        
        if (p1 != p2) {
            
            A = p1;
            min = std::min(min, m1);
            max = std::max(max, M1);
            
            B = p2;
            min = std::min(min, m2);
            max = std::max(max, M2);
        }
    }
    
    const auto& [p1, m1, M1] = parents[A][0];
    const auto& [p2, m2, M2] = parents[B][0];
    
    min = std::min(min, m1);
    max = std::max(max, M1);
    
    min = std::min(min, m2);
    max = std::max(max, M2);
    
    return {min, max};
}



int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    while (--N) {
        
        std::cin >> A >> B >> C;
        adjL[A].push_back({C, B});
        adjL[B].push_back({C, A});
    }
    
    init(1, 0, 0);
    
    std::cin >> K;
    
    while (K--) {
        
        std::cin >> A >> B;
        
        auto [min, max] = LCA(A, B);
        
        std::cout << min << ' ' << max << '\n';
    }
    
    return 0;
}

