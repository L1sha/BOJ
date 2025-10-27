#include "bits/stdc++.h"

constexpr int N_MAX = 100, M_MAX = 100;

int N, M, source, sink;

std::array<std::array<char, M_MAX>, N_MAX> map;
std::array<std::vector<int>, N_MAX * M_MAX * 2> adjL;
std::array<std::array<bool, 5>, N_MAX * M_MAX * 2> able;


        
void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            std::cin >> map[row][col];
        }
    }
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            if (map[row][col] == '#') continue;
            if (map[row][col] == 'K') source = row * M + col;
            else if (map[row][col] == 'H') sink = row * M + col + N * M;
            
            if (row != 0 && map[row - 1][col] != '#') {
                
                adjL[row * M + col].push_back((row - 1) * M + col + N * M);
                able[row * M + col][1] = true;
                adjL[(row - 1) * M + col + N * M].push_back(row * M + col);
                
                adjL[(row - 1) * M + col].push_back(row * M + col + N * M);
                able[(row - 1) * M + col][2] = true;
                adjL[row * M + col + N * M].push_back((row - 1) * M + col);
            }
            
            if (col != 0 && map[row][col - 1] != '#') {
                
                adjL[row * M + col].push_back(row * M + col - 1 + N * M);
                able[row * M + col][3] = true;
                adjL[row * M + col - 1 + N * M].push_back(row * M + col);
                
                adjL[row * M + col - 1].push_back(row * M + col + N * M);
                able[row * M + col - 1][4] = true;
                adjL[row * M + col + N * M].push_back(row * M + col - 1);
            }
            
            adjL[row * M + col + N * M].push_back(row * M + col);
            able[row * M + col + N * M][0] = true;
            adjL[row * M + col].push_back(row * M + col + N * M);
        }
    }
}

int getDir(int cursor, int next) {
    
    int diff = (next % (N * M)) - (cursor % (N * M));
    
    if (diff == 0) return 0;
    if (diff == -M) return 1;
    if (diff == M) return 2;
    if (diff == -1) return 3;
    if (diff == 1) return 4;
    
    return -1;
}

void solve() {
    
    std::vector<int> prev(N * M * 2);
    std::bitset<N_MAX * M_MAX * 2> visited;
    int res = 0;
    
    while (true) {
        
        std::fill(prev.begin(), prev.end(), -1);
        visited.reset();
        
        std::queue<int> q;
        q.push(source);
        prev[source] = source;
        visited[source] = true;
        
        for (int cursor; !q.empty(); ) {
            
            cursor = q.front();
            q.pop();
            
            if (cursor == sink) break;
            
            for (const int& next : adjL[cursor]) {
                
                if (!visited[next] && able[cursor][getDir(cursor, next)]) {
                    
                    prev[next] = cursor;
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        
        if (prev[sink] == -1) break;
        if (prev[sink] == source) {
            
            std::cout << -1;
            return;
        }
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            able[prev[cursor]][getDir(prev[cursor], cursor)] = false;
            able[cursor][getDir(cursor, prev[cursor])] = true;
        }
        
        res++;
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}