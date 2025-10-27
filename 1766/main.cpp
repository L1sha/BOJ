#include "bits/stdc++.h"


int N, M;
std::array<std::vector<int>, 32001> adjL;
std::array<int, 32001> inDegree;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    int from, to;
    while (M--) {
        
        std::cin >> from >> to; 
        inDegree[to]++;
        adjL[from].push_back(to);
    }
    
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int idx = 1; idx <= N; ++idx) if (!inDegree[idx]) pq.push(idx);
    
    int top;
    while (!pq.empty()) {
        
        top = pq.top();
        pq.pop();
        std::cout << top << ' ';
        for (auto& el : adjL[top]) if (!(--inDegree[el])) pq.push(el);
    }
    
    return 0;
}

