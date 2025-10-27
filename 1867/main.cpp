#include "bits/stdc++.h"

constexpr int N_MAX = 500;

int N, K;

std::array<std::vector<int>, N_MAX> adjL;
std::array<int, N_MAX> occupied;
std::bitset<N_MAX> visited;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K;
    
    for (int row, col; K--; ) {
        
        std::cin >> row >> col;
        
        adjL[row - 1].push_back(col - 1);
    }
}

int binaryMatching(const int& cursor) {
    
    for (const int& next : adjL[cursor]) {
        
        if (!visited[next]) {
            
            visited[next] = true;
            
            if (occupied[next] == -1 || binaryMatching(occupied[next])) {
                
                occupied[next] = cursor;
                return 1;
            }
        }
    }
    
    return 0;
}

void solve() {
    
    std::fill(occupied.begin(), occupied.begin() + N, -1);
    
    int res = 0;
    
    for (int idx = 0; idx < N; ++idx) {
        
        visited.reset();
        
        res += binaryMatching(idx);
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

