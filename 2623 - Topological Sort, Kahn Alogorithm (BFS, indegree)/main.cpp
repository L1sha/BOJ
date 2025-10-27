#include "bits/stdc++.h"


int N, M, S;

std::array<std::vector<int>, 1001> adjL;
std::array<int, 1001> indegree;
std::array<bool, 1001> done;
std::array<std::unordered_set<int>, 1001> onlyOne;
std::vector<int> res;
std::queue<int> q;

void solve(int idx){
    
    q.push(idx);
    
    int front;
    
    while (!q.empty()){
        
        front = q.front();
        q.pop();
        res.push_back(front);
        done[front] = true;
        
        for (auto& el : adjL[front]) if(--indegree[el] == 0) q.push(el);
    }
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    int from, to;
    
    while (M--){
        
        std::cin >> S;
        
        std::cin >> from;

        while (--S){
            
            std::cin >> to;
            
            if (onlyOne[from].find(to) == onlyOne[from].end()){
                
                adjL[from].push_back(to);
                indegree[to]++;
                onlyOne[from].insert(to);    
            }
            
            from = to;
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) if (!indegree[idx] && !done[idx]) solve(idx);
    
    if (res.size() != N) std::cout << 0;
    else for (auto& el : res) std::cout << el << '\n';
    
    return 0;
}





