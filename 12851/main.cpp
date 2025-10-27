#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, K;

std::array<int, 100'001> minTime;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    std::fill(minTime.begin(), minTime.end(), -1);
    
    std::queue<intPair> q;
    q.push({N, 0});
    
    intPair front;
    int res = 100'001, cnt = 0;
    
    while (!q.empty()) {
        
        front = q.front();
        q.pop();
        
        if (front.second > res) break;
        
        if (front.first == K) {
            
            res = front.second;
            cnt++;
        }
        
        if (minTime[front.first] == -1) minTime[front.first] = front.second;
        else if (front.second > minTime[front.first]) continue;
        
        if (front.first - 1 >= 0 && minTime[front.first - 1] == -1) q.push({front.first - 1, front.second + 1});
        if (front.first + 1 <= 100'000 && minTime[front.first + 1] == -1) q.push({front.first + 1, front.second + 1});
        if (front.first * 2 <= 100'000 && minTime[front.first * 2] == -1) q.push({front.first * 2, front.second + 1});
    }
    
    std::cout << res << '\n' << cnt;
    
    return 0;
}


