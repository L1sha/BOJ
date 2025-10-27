#include "bits/stdc++.h"

constexpr int N_MAX = 200'000;

int N, Q;

std::vector<int> parents, representative;
std::vector<std::pair<int, int>> queries;
std::vector<bool> res;

int getRepresentative(int curr) {
    
    if (curr == representative[curr]) return curr;
    return representative[curr] = getRepresentative(representative[curr]);
}

void doUnion(int left, int right) {
    
    representative[getRepresentative(right)] = getRepresentative(left);
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
    
    queries.resize(N - 1 + Q);
    for (auto& query : queries) {
        
        std::cin >> query.second;
        if (query.second) std::cin >> query.first >> query.second;
        else std::cin >> query.first;
    }
    
    res.reserve(Q);
}

void solve() {
    
    std::reverse(queries.begin(), queries.end());
    
    for (const auto& [first, second] : queries) {
        
        if (second) {
            
            res.push_back(getRepresentative(first) == getRepresentative(second));
        }
        else {
            
            doUnion(first, parents[first]);
        }
    }
    
    std::reverse(res.begin(), res.end());
    
    for (const auto& el : res) std::cout << (el ? "YES" : "NO") << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}