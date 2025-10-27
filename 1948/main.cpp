#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M, S, E, W;
std::array<std::vector<intPair>, 10'001> adjL;
std::array<int, 10'001> max;
std::array<std::vector<int>, 10'001> maxNext;
std::bitset<10'001> isDone;


void DFS(int cursor) {
    
    int cnt = 0, curMax = 0;
    std::vector<int> curMaxNext;
    
    for (const auto& [weight, next] : adjL[cursor]) {
        
        if (!isDone[next]) {
            
            DFS(next);
        }
        
        if (max[next] + weight > curMax) {
            
            curMax = max[next] + weight;
            curMaxNext.clear();
            curMaxNext.push_back(next);
        }
        else if (max[next] + weight == curMax) {
            
            curMaxNext.push_back(next);
        }
    }
    
    max[cursor] = curMax;
    maxNext[cursor] = std::move(curMaxNext);
    isDone[cursor] = true;
}

int count() {
    
    int cnt = 0;
    std::queue<int> q;
    q.push(S);
    isDone.reset();
    isDone[S] = true;
    
    while (!q.empty()) {
        
        cnt += maxNext[q.front()].size();
        
        for (const int& next : maxNext[q.front()]) {
            
            if (!isDone[next]) {
                
                isDone[next] = true;
                q.push(next);
            }
        }
        
        q.pop();
    }
    
    return cnt;
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    while (M--) {
        
        std::cin >> S >> E >> W;
        adjL[S].push_back({W, E});
    }
    std::cin >> S >> E;
    
    DFS(S);
    
    std::cout << max[S] << '\n' << count();
    
    return 0;
}

