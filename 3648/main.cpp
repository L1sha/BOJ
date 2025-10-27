#include "bits/stdc++.h"


bool res;
int N, M, A, B, cnt;
std::array<std::vector<int>, 2000> adjL;
std::array<int, 2000> visited;
std::bitset<2000> isFinished;
std::stack<int> stk;

void clear() {
    
    res = true;
    cnt = 0;
    for (auto& el : adjL) {
        
        el.clear();
    }
    std::fill(visited.begin(), visited.end(), 0);
    isFinished.reset();
    while (!stk.empty()) {
        
        stk.pop();
    }
}

int convert(int input) {
    
    if (input < 0) {
        
        return -input + 1000;
    }
    
    return input;
}

int Tarjan(const int cursor) {
    
    int lowestDest = visited[cursor] = ++cnt;
    stk.push(cursor);
    
    for (const int& next : adjL[cursor]) {
        
        if (visited[next]) {
            
            if (!isFinished[next]) {
                
                lowestDest = std::min(lowestDest, visited[next]);
            }
        }
        else {
            
            lowestDest = std::min(lowestDest, Tarjan(next));
        }
    }
    
    if (lowestDest == visited[cursor]) {
        
        std::bitset<2000> SCC;
        
        while (stk.top() != cursor) {
            
            SCC[stk.top()] = true;
            isFinished[stk.top()] = true;
            
            if (SCC[(stk.top() + 1000) % 2000]) {
                
                res = false;
            }
            
            stk.pop();
        }
        
        isFinished[cursor] = true;
            
        if (SCC[(cursor + 1000) % 2000]) {
            
            res = false;
        }
        
        stk.pop();
    }
    
    return lowestDest;
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    while (std::cin >> N >> M) {
        
        clear();
        
        while (M--) {
            
            std::cin >> A >> B;
            adjL[convert(-A)].push_back(convert(B));
            adjL[convert(-B)].push_back(convert(A));
        }
        adjL[convert(-1)].push_back(1);
        
        for (int idx = 1; idx <= N; ++idx) {
            
            if (!visited[idx]) {
                
                Tarjan(idx);
            }
            
            if (!visited[idx + 1000]) {
                
                Tarjan(idx + 1000);
            }
        }
        
        if (res) {
            
            std::cout << "yes\n";
        }
        else {
            
            std::cout << "no\n";
        }
    }
    
    return 0;
}

