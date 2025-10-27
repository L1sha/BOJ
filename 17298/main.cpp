#include "bits/stdc++.h"


int N;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    std::stack<std::pair<int, int>> s;
    std::vector<int> res(N, -1);
    int temp;
    std::pair<int, int> top;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> temp;
        while (!s.empty() && (top = s.top()).first < temp) {
            
            s.pop();
            res[top.second] = temp;
        }
        s.push({temp, idx});
    }
    
    for (auto& el: res) std::cout << el << ' ';
    
    return 0;
}

