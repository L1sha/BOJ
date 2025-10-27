#include "bits/stdc++.h"

constexpr int N_MAX = 500'000;

int N, Q;

std::vector<std::set<int>> sets;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> Q;
    sets.resize(N + 1);
    
    for (int size, input, idx = 1; idx <= N; ++idx) {
        
        std::cin >> size;
        while (size--) {
            
            std::cin >> input;
            sets[idx].insert(input);
        }
    }
}

void doUnion(int a, int b) {
    
    if (sets[a].size() < sets[b].size()) std::swap(sets[a], sets[b]);
    
    for (const auto& el : sets[b]) sets[a].insert(el);
    
    sets[b].clear();
}

int returnSize(int curr) {
    
    return sets[curr].size();
}

void solve() {
    
    for (int query, a, b; Q--; ) {
        
        std::cin >> query;
        
        if (query == 1) {
            
            std::cin >> a >> b;
            doUnion(a, b);
        }
        else {
            
            std::cin >> a;
            std::cout << returnSize(a) << '\n';
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}