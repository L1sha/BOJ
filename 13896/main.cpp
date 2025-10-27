#include "bits/stdc++.h"

constexpr int N_MAX = 100'000, Q_MAX = 50'000;

int N, Q, capital, LOGN;

std::vector<std::vector<int>> adjL, LCA;
std::array<int, N_MAX + 1> height, subTreeNodeNum;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> Q >> capital;
    LOGN = ceil(log2(N)) + 1;
    
    adjL.clear();
    adjL.resize(N + 1);
    
    LCA.clear();
    LCA.resize(N + 1, std::vector<int>(LOGN));
    
    for (int from, to, idx = 0; idx < N - 1; ++idx) {
        
        std::cin >> from >> to;
        
        adjL[from].push_back(to);
        adjL[to].push_back(from);
    }
}

void makeLCA(int cursor = 1, int parent = 0) {
    
    height[cursor] = height[parent] + 1;
    subTreeNodeNum[cursor] = 1;
    LCA[cursor][0] = parent;
    
    for (int mid, idx = 1; idx < LOGN; ++idx) {
        
        mid = LCA[cursor][idx - 1];
        
        if (mid) {
            
            LCA[cursor][idx] = LCA[mid][idx - 1];
        }
        else break;
    }
    
    for (const auto& next : adjL[cursor]) {
        
        if (next != parent) {
            
            makeLCA(next, cursor);
            subTreeNodeNum[cursor] += subTreeNodeNum[next];
        }
    }
}

int howManyCitiesHandleTax(const auto& U) {
    
    if (U == capital) return N;
    
    int left = U, right = capital, oneBefore;
    
    if (height[left] != height[right]) {
        
        if (height[left] < height[right]) std::swap(left, right);
        
        for (int idx = LOGN - 1; idx >= 0; --idx) {
            
            if (height[LCA[left][idx]] > height[right]) {
                
                left = LCA[left][idx];
            }
        }
        
        oneBefore = left;
        left = LCA[left][0];
    }
    
    if (left == right) {
        
        if (left == capital) {
            
            return subTreeNodeNum[U];
        }
        else {  // left == U
            
            return N - subTreeNodeNum[oneBefore];
        }
    }
    else {
        
        return subTreeNodeNum[U];
    }
}

void solve() {
    
    static int testcase = 0;
    std::cout << "Case #" << ++testcase << ":\n";
    
    makeLCA();
    
    for (int S, U; Q--; ) {
        
        std::cin >> S >> U;
        
        if (S) {
            
            std::cout << howManyCitiesHandleTax(U) << '\n'; 
        }
        else {
            
            capital = U;
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    int T; std::cin >> T;
    while (T--) {
        
        get_input();
        solve();
    }
    
    return 0;
}