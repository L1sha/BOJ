#include "bits/stdc++.h"


int N;

std::array<int, 1'000'001> from;
std::queue<int> q;
std::deque<int> dq;

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    q.push(N);
    from[N] = -1;
    int top;
    
    while (!q.empty()) {
        
        top = q.front();
        q.pop();
        
        if (top == 1) break;
        
        if (!(top % 3) && !from[top / 3]) {
            
            q.push(top / 3);
            from[top / 3] = top;
        }
        if (!(top % 2) && !from[top / 2]){
            
            q.push(top / 2);
            from[top / 2] = top;
        }
        if (!from[top - 1]) {
            
            q.push(top - 1);
            from[top - 1] = top;
        }
    }
    
    int cursor = 1;
    
    while (cursor != -1) {
        
        dq.push_front(cursor);
        cursor = from[cursor];
    }
    
    std::cout << dq.size() - 1 << '\n';
    for (auto& el : dq) std::cout << el << ' ';
    
    return 0;
}

