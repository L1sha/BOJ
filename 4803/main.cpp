#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M, from, to, cnt, t;
bool isTree;

std::array<std::vector<int>, 501> adjL;
std::array<bool, 501> visited;
std::stack<intPair> s;


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    while (++t) {
    
        std::cin >> N >> M;
        
        if (!N && !M) break;
        
        cnt = 0;
        std::fill(visited.begin() + 1, visited.begin() + N + 1, false);
        
        while (M--) {
            
            std::cin >> from >> to;
            adjL[from].push_back(to);
            adjL[to].push_back(from);
        }
        
        for (int idx = 1; idx <= N; ++idx) if (!visited[idx]) {
            
            isTree = true;
            s.push({idx, 0});
            
            while (!s.empty()) {
                
                auto [top, parent] = s.top();
                s.pop();
                
                if (visited[top]) continue;
                visited[top] = true;
                
                for (auto& el : adjL[top]) {
                    
                    if (visited[el] && el != parent) isTree = false;
                    else s.push({el, top});
                }
            }
            
            if (isTree) cnt++;
        }
        
        std::cout << "Case " << t << ": ";
        if (cnt > 1) std::cout << "A forest of " << cnt << " trees.\n";
        else if (cnt == 1) std::cout << "There is one tree.\n";
        else std::cout << "No trees.\n";
        
        for (int idx = 1; idx <= N; ++idx) adjL[idx].clear();
    }
    
    return 0;
}

