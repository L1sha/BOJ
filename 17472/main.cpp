#include "bits/stdc++.h"


// island C can exist between island A and B....


using intPair = std::pair<int, int>;

int N, M, res;
std::array<std::array<int, 10>, 10> map;
std::array<std::array<bool, 10>, 10> visited;
std::vector<std::vector<intPair>> islands;
std::vector<std::tuple<int, int, int>> bridges;
std::vector<int> parent;

int getParent(int idx) {
    
    if (idx != parent[idx]) return parent[idx] = getParent(parent[idx]);
    return idx;
}

void Union(int idx1, int idx2) {
    
    parent[getParent(idx2)] = getParent(idx1);
}

std::vector<intPair> makeNewIsland (int row, int col) {
    
    std::vector<intPair> newIsland;
    std::queue<intPair> q;
    std::array<intPair, 4> candidates;
    
    q.push({row, col});
    visited[row][col] = true;
    
    while (!q.empty()) {
        
        auto [r, c] = q.front();
        q.pop();
        
        newIsland.push_back({r, c});
        
        candidates[0] = {r - 1, c};
        candidates[1] = {r + 1, c};
        candidates[2] = {r, c - 1};
        candidates[3] = {r, c + 1};
        
        for (auto& [cr, cc] : candidates) {
            
            if (cr >= 0 && cr < N && cc >= 0 && cc < M && map[cr][cc] && !visited[cr][cc]) {
                
                q.push({cr, cc});
                visited[cr][cc] = true;
            }
        }
    }
    
    return newIsland;
}

int getDistance(int idx1, int idx2) {
    
    int min = INT_MAX, temp;
    
    for (auto& [r1, c1] : islands[idx1]) {
        
        for (auto& [r2, c2] : islands[idx2]) {
            
            if (r1 == r2) {
                
                temp = std::abs(c1 - c2) - 1;
                
                for (int col = std::min(c1, c2) + 1; col < std::max(c1, c2); ++col) {
                    
                    if (map[r1][col]) {
                        
                        temp = 0;
                        break;
                    }
                }
                
                if (temp > 1) {
                    
                    min = std::min(min, temp);
                }
            }
            else if (c1 == c2) {
                
                temp = std::abs(r1 - r2) - 1;
                
                for (int row = std::min(r1, r2) + 1; row < std::max(r1, r2); ++row) {
                    
                    if (map[row][c1]) {
                        
                        temp = 0;
                        break;
                    }
                }
                
                if (temp > 1) {
                    
                    min = std::min(min, temp);
                }
            }
        }
    }
    
    if (min == INT_MAX) {
        
        min = 0;
    }
    
    return min;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            std::cin >> map[row][col];
        }
    }
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            if (map[row][col] && !visited[row][col]) {
                
                islands.push_back(makeNewIsland(row, col));
                parent.push_back(parent.size());
            }
        }
    }
    
    int cnt = islands.size();
    
    for (int idx1 = 0; idx1 < cnt; ++idx1) {
        
        for (int idx2 = idx1 + 1; idx2 < cnt; ++idx2) {
            
            if (int dist = getDistance(idx1, idx2)) {
                
                bridges.push_back({dist, idx1, idx2});
            }
        }
    }
    
    std::sort(bridges.begin(), bridges.end());
    
    for (auto& [dist, idx1, idx2] : bridges) {
        
        if (getParent(idx1) == getParent(idx2)) continue;
        
        res += dist;
        Union(idx1, idx2);
        cnt--;
    }
    
    if (cnt == 1) {
        
        std::cout << res;
    }
    else {
        
        std::cout << -1;
    }
    
    return 0;
}

