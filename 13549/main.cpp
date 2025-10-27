#include "bits/stdc++.h"


int N, K;

std::unordered_set<int> visited;
std::queue<std::pair<int, int>> q;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    if (N != 0) while (N <= 1e5) {
        
        q.push({N, 0});
        visited.insert(N);
        N *= 2;
    }
    else { 
        
        q.push({0, 0});
        visited.insert(0);
    }
    
    int next;
    
    while (true){
        
        auto front = q.front();
        q.pop();
        
        if (front.first == K) { std::cout << front.second; break; }
        
        visited.insert(front.first);
        
        next = front.first + 1;
        while (!visited.count(next) && next <= 1e5) { 
            
            q.push({next, front.second + 1});
            visited.insert(next);
            next *= 2;
        }
        
        next = front.first - 1;
        if (next >= 1) while (!visited.count(next) && next <= 1e5) { 
            
            q.push({next, front.second + 1}); 
            visited.insert(next);
            next *= 2; 
        }
        else if (next == 0 && !visited.count(0)) {
            
            q.push({0, front.second + 1});
            visited.insert(0);
        }
    }
    
    
    return 0;
}


