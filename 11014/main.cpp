#include "bits/stdc++.h"

constexpr int N_MAX = 80, M_MAX = 80, halfM_MAX = (M_MAX + 1) / 2;

int C, N, M;

std::array<char, N_MAX * M_MAX> map;
std::array<std::vector<int>, N_MAX * halfM_MAX> adjL;
std::array<int, N_MAX * halfM_MAX> occupied;
std::bitset<N_MAX * halfM_MAX> visited;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    for (int idx = 0; idx < N * M; ++idx) std::cin >> map[idx];
}

bool binaryMatching(const int& cursor) {
    
    for (const int& next : adjL[cursor]) {
        
        if (!visited[next]) {
            
            visited[next] = true;
            
            if (occupied[next] == -1 || binaryMatching(occupied[next])) {
                
                occupied[next] = cursor;
                return true;
            }
        }
    }
    
    return false;
}

void solve() {
    
    int halfM = (M + 1) / 2;
    
    for (int idx = 0; idx < N * halfM; ++idx) adjL[idx].clear();
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; col += 2) {
            
            if (map[row * M + col] == '.') {
                
                if (row != 0) {
                    
                    if (col != 0 && map[(row - 1) * M + (col - 1)] == '.') {
                        
                        adjL[row * halfM + col / 2].push_back((row - 1) * halfM + (col / 2 - 1));
                    }
                    if (col != M - 1 && map[(row - 1) * M + (col + 1)] == '.') {
                        
                        adjL[row * halfM + col / 2].push_back((row - 1) * halfM + col / 2);
                    }
                }
                
                if (col != 0 && map[row * M + (col - 1)] == '.') {
                    
                    adjL[row * halfM + col / 2].push_back(row * halfM + (col / 2 - 1));
                }
                
                if (col != M - 1 && map[row * M + (col + 1)] == '.') {
                    
                    adjL[row * halfM + col / 2].push_back(row * halfM + col / 2);
                }
            }
        }
    }
    
    int ans = N * M, maxMatching = 0;
    std::fill(occupied.begin(), occupied.begin() + N * M, -1);
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            if (map[row * M + col] == 'x') ans--;
            else if (M % 2 == 0) {
                
                visited.reset();
                maxMatching += binaryMatching(N * halfM + col / 2);
            }
        }
    }
    
    std::cout << ans - maxMatching << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    
    std::cin >> C;
    
    while (C--) {
        
        get_input();
        solve();
    }
    
    return 0;
}

