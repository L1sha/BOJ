#include "bits/stdc++.h"


int N, K;

std::queue<int> q;
std::array<bool, 100'001> visited;

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    int res = 0, num, temp;
    q.push(N);
    
    while (true){
        
        num = q.size();
        
        while (num--) { 
            
            temp = q.front();
            q.pop();
            if (temp == K) { std::cout << res; return 0; }
            if (temp > 0 && !visited[temp - 1]) { q.push(temp - 1); visited[temp - 1] = true; }
            if (temp < 100'000 && !visited[temp + 1]) { q.push(temp + 1); visited[temp + 1] = true; }
            if (temp <= 50'000 && !visited[temp * 2]) { q.push(temp * 2); visited[temp * 2] = true; }
        }
        
        res++;
    }
    
    return 0;
}


