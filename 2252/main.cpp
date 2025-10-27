#include "bits/stdc++.h"


int N, M;
std::array<std::vector<int>, 32'001> adjL;
std::array<bool, 32'001> IamTall;
std::array<std::pair<int, int>, 32'001> res;

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    int from, to;
    
    while (M--){
        
        std::cin >> from >> to;
        adjL[from].push_back(to);
        IamTall[to] = true;
    }
    
    int cursor = 0;
    
    for (int idx = 1; idx <= N; ++idx) if (!IamTall[idx]){
        
        res[idx] = { cursor, idx };
        
        std::queue<std::pair<int, int>> q;
        q.push(res[idx]);
        
        std::pair<int, int> front;
        int nextRank;
        
        while (!q.empty()){
            
            auto front = q.front();
            q.pop();
            
            cursor = front.first + 1;            
            
            for (auto& el : adjL[front.second]){
                
                if (res[el].first < cursor) {
                    
                    res[el] = { cursor, el };
                    q.push(res[el]);
                }
            }
        }
    }
    
    std::sort(res.begin() + 1, res.begin() + N + 1);
    
    for (int idx = 1; idx <= N; ++idx) std::cout << res[idx].second << ' ';
    
    return 0;
}


