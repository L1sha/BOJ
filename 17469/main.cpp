#include "bits/stdc++.h"

constexpr int N_MAX = 100'000, Q_MAX = 1'000'000;

int N, Q;

std::vector<std::set<int>> sets;
std::vector<int> parents, representative;
std::vector<std::pair<int, int>> queries;
std::vector<int> res;

int getRepresentative(int curr) {
    
    if (curr == representative[curr]) return curr;
    return representative[curr] = getRepresentative(representative[curr]);
}

void doUnion(int left, int right) {
    
    int pL = getRepresentative(left), pR = getRepresentative(right);
    
    if (sets[pL].size() < sets[pR].size()) {
        
        std::swap(pL, pR);
    }
    
    representative[pR] = pL;
    
    for (const auto& el : sets[pR]) sets[pL].insert(el);
    
    sets[pR].clear();
}


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> Q;
    
    representative.resize(N + 1);
    std::iota(representative.begin(), representative.end(), 0);
    
    parents.resize(N + 1);
    for (int idx = 2; idx <= N; ++idx) std::cin >> parents[idx];
    
    sets.resize(N + 1);
    for (int input, idx = 1; idx <= N; ++idx) {
        
        std::cin >> input;
        sets[idx].insert(input);
    }
    
    queries.resize(N - 1 + Q);
    for (auto& query : queries) std::cin >> query.first >> query.second;
    
    res.reserve(Q);
}

void solve() {
    
    std::reverse(queries.begin(), queries.end());
    
    for (const auto& [first, second] : queries) {
        
        if (first == 2) {
            
            res.push_back(sets[getRepresentative(second)].size());
        }
        else {
            
            doUnion(second, parents[second]);
        }
    }
    
    std::reverse(res.begin(), res.end());
    
    for (const auto& el : res) std::cout << el << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}