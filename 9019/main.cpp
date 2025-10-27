#include "bits/stdc++.h"


int T, A, B, front;

std::array<int, 4> next;
std::array<char, 4> convert;
std::array<std::pair<int, char>, 10000> res;
std::string output;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    convert = {'D', 'S', 'L', 'R'};
    
    while (T--) {
        
        std::cin >> A >> B;
        
        output.clear();
        std::fill(res.begin(), res.end(), std::make_pair(-1, 'X'));
        
        std::queue<int> q;
        q.push(A);
        res[A] = {10000, 0};
        
        while (!q.empty()) {
            
            front = q.front();
            q.pop();
            
            if (front == B) break;
            
            next = {(front * 2) % 10000, (front + 9999) % 10000, (front % 1000) * 10 + front / 1000, (front % 10) * 1000 + front / 10};
            
            for (int idx = 0; idx < 4; ++idx) {
                
                if (res[next[idx]].first >= 0) continue;
                res[next[idx]] = {front, convert[idx]};
                q.push(next[idx]);
            }
        }
        
        while (true) {
            
            if (front == A) break;
            output = res[front].second + output;
            front = res[front].first;
        }
        
        std::cout << output << '\n';
    }
    
    return 0;
}

