#include "bits/stdc++.h"



int T, N, M;
std::array<std::vector<int>, 501> adjL;
std::array<int, 501> indegree;



void solve() {
    
    int flag = 1;
    bool unique;
    
    std::vector<bool> visited(N + 1);
    std::vector<int> rank;
    
    for (int idx = 1; idx <= N; ++idx) {
            
        if (!visited[idx] && !indegree[idx]) {
            
            std::queue<int> q;
            q.push(idx);
            
            int front;
            
            while (!q.empty()) {
                
                front = q.front();
                q.pop();
                
                rank.push_back(front);
                visited[front] = true;
                unique = false;
                
                for (auto& el : adjL[front]) {
                    
                    if (--indegree[el] == 0) {
                        
                        q.push(el);
                        
                        if (unique) {
                            
                            flag = 0;
                        }
                        
                        unique = true;
                    }
                }
            }
            
            if (rank.size() != N) {
                
                flag = 0;
            }
        }
    }
    
    if (rank.size() != N) {
        
        flag = -1;
    }
    
    switch (flag) {
        
        case 1:
        
        for (auto& el : rank) {
            
            std::cout << el << ' ';
        }
        std::cout << '\n';
        
        break;
        
        case 0:
        
        std::cout << "?\n";
        
        break;
        
        case -1:
        
        std::cout << "IMPOSSIBLE\n";
        
        break;
    }
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> N;
        
        for (int idx = 1; idx <= N; ++idx) {
            
            adjL[idx].clear();
            indegree[idx] = 0;
        }
        
        int rank = 1, team1, team2;
        std::vector<std::vector<bool>> inserted(N + 1, std::vector<bool>(N + 1));
        std::unordered_map<int, int> lastYear;
        
        for (int idx = 0; idx < N; ++idx) {
            
            std::cin >> team1;
            lastYear[team1] = rank++;
        }
        
        std::cin >> M;
        
        while (M--) {
            
            std::cin >> team1 >> team2;
            
            if (lastYear[team1] < lastYear[team2]) {
                
                adjL[team2].push_back(team1);
                indegree[team1]++;
            }
            else {
                
                adjL[team1].push_back(team2);
                indegree[team2]++;
            }
            
            inserted[team1][team2] = true;
            inserted[team2][team1] = true;
        }
        
        for (team1 = 1; team1 <= N; ++team1) {
            
            for (team2 = team1 + 1; team2 <= N; ++team2) {
                
                if (!inserted[team1][team2]) {
                    
                    if (lastYear[team2] < lastYear[team1]) {
                        
                        adjL[team2].push_back(team1);
                        indegree[team1]++;
                    }
                    else {
                        
                        adjL[team1].push_back(team2);
                        indegree[team2]++;
                    }
                }
            }
        }
        
        solve();
    }
    
    return 0;
}