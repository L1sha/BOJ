#include "bits/stdc++.h"


int N, from, to;
std::array<std::vector<int>, 10'001> adjL;
std::array<int, 10'001> weight;
std::array<int, 10'001> withMyself;
std::array<int, 10'001> woMyself;

void solve(int cursor, int parent) {
    
    withMyself[cursor] = weight[cursor];
    
    for (const int& next : adjL[cursor]) {
        
        if (next == parent) {
            
            continue;
        }
        
        solve(next, cursor);
        
        withMyself[cursor] += woMyself[next];
        woMyself[cursor] += std::max(withMyself[next], woMyself[next]);
    }
}

void getList(int cursor, int parent, std::vector<int>& res, bool sw) {
    
    if (sw && withMyself[cursor] > woMyself[cursor]) {
        
        res.push_back(cursor);
        
        sw = false;
    }
    else {
        
        sw = true;
    }
    
    for (const int& next : adjL[cursor]) {
        
        if (next == parent) {
            
            continue;
        }
        
        getList(next, cursor, res, sw);
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
    
    std::cout << std::max(withMyself[1], woMyself[1]) << '\n';
    
    std::vector<int> res;
    
    getList(1, 0, res, true);
    
    std::sort(res.begin(), res.end());
    
    for (const auto& el : res) {
        
        std::cout << el << ' ';
    }
    
    return 0;
}

