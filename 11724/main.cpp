#include "bits/stdc++.h"


int N, M;

std::array<std::vector<int>, 1001> adjL;
std::array<bool, 1001> visited;
std::queue<int> q;


void BFS(int idx){
    
    int temp;
    
    q.push(idx);
    
    while (!q.empty()){
        
        temp = q.front();
        q.pop();
        if (visited[temp]) continue;
        visited[temp] = true;
        
        for (const auto& el : adjL[temp]) if (!visited[el]) q.push(el);
    }
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M; 
    
    int temp1, temp2;
    
    while (M--){
        
        std::cin >> temp1 >> temp2;
        
        adjL[temp1].push_back(temp2);
        adjL[temp2].push_back(temp1);
    }
    
    int res = 0;
    
    for (int idx = 1; idx <= N; ++idx) if (!visited[idx]){
        
        BFS(idx);
        res++;
    }
    
    std::cout << res;
    
    return 0;
}


