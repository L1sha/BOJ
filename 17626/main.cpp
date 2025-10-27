#include <iostream>
#include <array>
#include <queue>

std::array<int, 50'001> res;

int main() {
    
    int N; std::cin >> N;
    
    std::queue<int> q;
    q.push(0);
    
    for (int front; !q.empty(); ) {
        
        front = q.front();
        q.pop();
        
        if (front == N) break;
        
        for (int next, toAdd = 1; (next = toAdd * toAdd + front) <= 50'000; ++toAdd) {
            
            if (res[next] == 0) {
                
                res[next] = res[front] + 1;
                q.push(next);
            }
        }
    }
    
    std::cout << res[N];
    
    return 0;
}