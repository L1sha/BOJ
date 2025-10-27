#include "bits/stdc++.h"


int N, K;
std::array<int, 100'001> from;
std::queue<int> q;
std::vector<int> res;
std::array<int, 3> next;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::fill(from.begin(), from.end(), -1);
    
    std::cin >> N >> K;
    
    q.push(N);
    from[N] = 100'001;
    int top;

    while (true) {
        
        top = q.front();
        q.pop();
        
        if (top == K) break;
        
        next = {top - 1, top + 1, top * 2};
        
        for (auto& el : next) {
            
            if (el < 0 || el > 100'000 || from[el] >= 0) continue;
            from[el] = top;
            q.push(el);
        }
    }
    
    while (top != 100'001) {
        
        res.push_back(top);
        top = from[top];
    }
    
    std::cout << res.size() - 1 << '\n';
    for (auto it = res.rbegin(); it != res.rend(); ++it) std::cout << *it << ' ';
    
    return 0;
}

