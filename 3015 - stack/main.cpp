#include "bits/stdc++.h"


int N;

std::stack<int> s;
std::unordered_map<int, int> acc;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    int temp;
    long long cnt = 0;
    
    while (N--) {
        
        std::cin >> temp;
        
        while (!s.empty() && s.top() < temp) {
            
            cnt = cnt + acc[s.top()];
            acc[s.top()] = 0;
            s.pop();
        }
        if (!s.empty() && s.top() == temp) {
            
            cnt = cnt + acc[s.top()];
            s.pop();
        }
        if (!s.empty()) cnt++;
        
        s.push(temp);
        
        if (acc.count(temp)) acc[temp]++;
        else acc[temp] = 1;
    }
    
    std::cout << cnt;
    
    return 0;
}

