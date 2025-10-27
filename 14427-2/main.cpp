#include "bits/stdc++.h"


int N, M, query, target, value;
using intPair = std::pair<int, int>;
std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> a;
std::array<int, 100'001> b;




int main(int argc, char* *argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int i = 1; i <= N; ++i) {
        
        std::cin >> b[i];
        a.push(std::make_pair(b[i], i));
    }
    
    std::cin >> M;
    
    while (M--){
        
        std::cin >> query;
        
        if (query == 1){
            
            std::cin >> target >> value;
            a.push(std::make_pair(value, target));
            b[target] = value;
        }
        else {
            
            while (b[a.top().second] != a.top().first) a.pop();
            std::cout << a.top().second << '\n';
        }
    }
    
    return 0;
}

