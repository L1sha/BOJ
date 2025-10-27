#include "bits/stdc++.h"


int N;

std::array<std::vector<int>, 100'001> adjL;
std::queue<std::pair<int, int>> q;
std::array<int, 100'001> parent;
std::array<bool, 100'001> visited;

void BFS(){
    
    q.push({1, 0});
    
    while (!q.empty()){
        
        auto temp = q.front();
        q.pop();
        
        if (visited[temp.first]) continue;
        visited[temp.first] = true;
        
        parent[temp.first] = temp.second;
        
        for (auto& el : adjL[temp.first]) if (!visited[el]) q.push({el, temp.first});
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int temp1, temp2;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> temp1 >> temp2;
        adjL[temp1].push_back(temp2);
        adjL[temp2].push_back(temp1);
    }
    
    BFS();
    
    for (int idx = 2; idx <= N; ++idx) std::cout << parent[idx] << '\n';
    
    return 0;
}


