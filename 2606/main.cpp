#include "bits/stdc++.h"


int N, M;

std::array<std::vector<int>, 101> adjL;
std::array<bool, 101> visited;
std::queue<int> q;


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
    
    int res = -1;
    
    q.push(1);
    
    while (!q.empty()){
        
        temp1 = q.front();
        q.pop();
        if (visited[temp1]) continue;
        visited[temp1] = true;
        res++;
        for (auto& el : adjL[temp1]) if (!visited[el]) q.push(el);
    }
    
    std::cout << res;
    
    return 0;
}


