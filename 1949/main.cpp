#include "bits/stdc++.h"


int N, from, to;
std::array<std::vector<int>, 10'001> adjL;
std::array<int, 10'001> weight;
std::array<int, 10'001> withMyself;
std::array<int, 10'001> woMyself;
std::array<int, 10'001> woMyself_atleastOne;

void solve(int cursor, int parent) {
    
    withMyself[cursor] = weight[cursor];
    
    bool atleastOne = false;
    int min = INT_MAX;
    
    for (const int& next : adjL[cursor]) {
        
        if (next == parent) {
            
            continue;
        }
        
        solve(next, cursor);
        
        withMyself[cursor] += woMyself[next];
        if (withMyself[next] >= woMyself_atleastOne[next]) {
            
            atleastOne = true;
            woMyself[cursor] += withMyself[next];
            woMyself_atleastOne[cursor] += withMyself[next];
        }
        else {
            
            woMyself[cursor] += woMyself_atleastOne[next];
            woMyself_atleastOne[cursor] += woMyself_atleastOne[next];    
        }
        
        min = std::min(min, woMyself_atleastOne[next] - withMyself[next]);
    }
    
    if (!atleastOne && min != INT_MAX) {
        
        woMyself_atleastOne[cursor] -= min;
    }
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> weight[idx];
    }
    
    for (int idx = 1; idx < N; ++idx) {
        
        std::cin >> from >> to;
        
        adjL[from].push_back(to);
        adjL[to].push_back(from);
    }
    
    solve(1, 0);
    
    std::cout << std::max(withMyself[1], woMyself_atleastOne[1]);
    
    return 0;
}

