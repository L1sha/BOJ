#include "bits/stdc++.h"


constexpr int K_MAX = 5001, DK_MAX = K_MAX * 2;

int K, N, cnt;
std::array<int, 3> L;
char C;
std::array<std::vector<int>, DK_MAX> adjL;
std::bitset<DK_MAX> done;
std::array<int, DK_MAX> visited;
std::vector<std::vector<int>> SCCs;
std::stack<int> stk;

int convert(int num) {
    
    if (num < 0) {
        
        return K_MAX - num;
    }
    
    return num;
}

int DFS(int cursor) {
    
    int leastDest = visited[cursor] = ++cnt;
    stk.push(cursor);
    
    for (const int& next : adjL[cursor]) {
        
        if (visited[next]) {
            
            if (!done[next]) {
                
                leastDest = std::min(leastDest, visited[next]);
            }
        }
        else {
            
            leastDest = std::min(leastDest, DFS(next));
        }
    }
    
    if (leastDest == visited[cursor]) {
        
        std::vector<int> newSCC;
        
        while (stk.top() != cursor) {
            
            done[stk.top()] = true;
            newSCC.push_back(stk.top());
            stk.pop();
        }
        
        done[cursor] = true;
        newSCC.push_back(cursor);
        stk.pop();
        
        SCCs.push_back(std::move(newSCC));
    }
    
    return leastDest;
}

bool makeSCC() {
    
    for (int idx = 1; idx <= K; ++idx) {
        
        if (!done[idx]) {
            
            DFS(idx);
        }
        
        if (!done[convert(-idx)]) {
            
            DFS(convert(-idx));
        }
    }
    
    std::bitset<K_MAX> check;
    
    for (const auto& SCC : SCCs) {
        
        check.reset();
        
        for (const auto& el : SCC) {
            
            if (check[el % K_MAX]) {
                
                return false;
            }
            
            check[el % K_MAX] = true;
        }
    }
    
    return true;
}

std::string solve() {
    
    std::string res(K, ' ');
    
    for (auto it = SCCs.rbegin(); it != SCCs.rend(); ++it) {
        
        if (res[(*it).front() % K_MAX - 1] != ' ') {
            
            continue;
        }
        
        for (const auto& el : (*it)) {
            
            if (el / K_MAX) {
                
                res[el % K_MAX - 1] = 'R';
            }
            else {
                
                res[el - 1] = 'B';
            }
        }
    }
    
    return res;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> K >> N;
    
    while (N--) {
        
        for (int idx = 0; idx < 3; ++idx) {
            
            std::cin >> L[idx] >> C;
            
            if (C == 'B') {
                
                L[idx] *= -1;
            }
        }
        
        adjL[convert(-L[0])].push_back(convert(L[1]));
        adjL[convert(-L[0])].push_back(convert(L[2]));
        adjL[convert(-L[1])].push_back(convert(L[0]));
        adjL[convert(-L[1])].push_back(convert(L[2]));
        adjL[convert(-L[2])].push_back(convert(L[0]));
        adjL[convert(-L[2])].push_back(convert(L[1]));
    }
    
    if (!makeSCC()) {
        
        std::cout << -1;
    }
    else {
        
        std::cout << solve();
    }
    
    return 0;
}

