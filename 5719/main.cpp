#include "bits/stdc++.h"


using intPair = std::pair<int, int>;


int N, M, S, D, U, V, P;

std::array<std::vector<intPair>, 500> adjL;
std::array<std::array<bool, 500>, 500> used;
std::array<std::vector<int>, 500> previous;
std::array<bool, 500> visited;


void fill_used(int cursor) {
    
    if (visited[cursor]) {
        
        return;
    }
    visited[cursor] = true;
    
    for (auto& prev : previous[cursor]) {
        
        used[prev][cursor] = true;
        fill_used(prev);
    }
}

int dijkstra() {
    
    std::vector<int> minDist(N, INT_MAX);
    std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> pq;
    
    pq.push({0, S});
    minDist[S] = 0;
    
    while (!pq.empty()) {
        
        auto [sum, cursor] = pq.top();
        pq.pop();
        
        if (sum > minDist[cursor]) {
            
            continue;
        }
        
        if (cursor == D) {
            
            return sum;
        }
        
        for (auto& [weight, next] : adjL[cursor]) {
            
            if (used[cursor][next]) {
                
                continue;
            }
            
            if (sum + weight < minDist[next]) {
                
                minDist[next] = sum + weight;
                previous[next].clear();
                previous[next].push_back(cursor);
                
                pq.push({sum + weight, next});
            }
            else if (sum + weight == minDist[next]) {
                
                previous[next].push_back(cursor);
            }
        }
    }
    
    return -1;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    while (true) {
        
        std::cin >> N >> M;
        
        if (N == 0 && M == 0) {
            
            break;
        }
        
        for (int idx = 0; idx < N; ++idx) {
            
            adjL[idx].clear();
            std::fill(used[idx].begin(), used[idx].begin() + N, false);
            previous[idx].clear();
            visited[idx] = false;
        }
        
        std::cin >> S >> D;
        
        while (M--) {
            
            std::cin >> U >> V >> P;
            
            adjL[U].push_back({P, V});
        }
        
        if (dijkstra() == -1) {
            
            std::cout << -1 << '\n';
            
            continue;
        }
        
        fill_used(D);
        
        std::cout << dijkstra() << '\n';
    }
    
    return 0;
}

