#include "bits/stdc++.h"


int A, B;

std::queue<std::pair<long long, int>> q;
std::unordered_set<long long> visited;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> A >> B;
    
    q.push({A, 1});
    
    int res = 1;
    
    while (true){
        
        auto front = q.front();
        q.pop();
        
        if (visited.count(front.first)) continue;
        
        if (res != front.second) {
            
            if (B < front.first) break;
            res = front.second;
        }
        
        if (front.first == B) { std::cout << res; return 0; }
         
        if (!visited.count(front.first * 2)) q.push({front.first * 2, front.second + 1});
        if (!visited.count(front.first * 10 + 1) && front.first * 10 + 1 <= 1e9) q.push({front.first * 10 + 1, front.second + 1});
    }
    
    std::cout << -1;
    
    return 0;
}


