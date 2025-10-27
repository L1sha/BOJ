#include "bits/stdc++.h"

int A, B, C;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> A >> B >> C;
}

bool check() {
    
    if (A == B && B == C) return true;
    
    if ((A + B + C) % 6 != 0) return false;
    
    int N = (A + B + C) / 3;
    
    while (N % 2 == 0) N /= 2;
    
    if (A % N + B % N + C % N != 0) return false;
    
    A /= N, B /= N, C /= N;
    
    N = A + B + C;
    
    std::vector<std::vector<bool>> visited(N / 3 + 1, std::vector<bool>(N / 2));
    
    std::array<int, 3> start = {A, B, C};
    std::sort(start.begin(), start.end());
    
    std::queue<std::array<int, 3>> q;
    q.push(start);
    visited[start[0]][start[1]] = true;
    
    while (!q.empty()) {
        
        auto [a, b, c] = q.front();
        q.pop();
        
        std::vector<std::array<int, 3>> next;
        
        if (a < b) {
            
            next.push_back({a + a, b - a, c});
            next.push_back({a + a, b, c - a});
        }
        if (b < c) next.push_back({a, b + b, c - b});
        
        for (auto& candidate : next) {
            
            std::sort(candidate.begin(), candidate.end());
            auto [nA, nB, nC] = candidate;
            
            if (nA == nB && nB == nC) return true;
            
            if (!visited[nA][nB]) {
                
                visited[nA][nB] = true;
                q.push(std::move(candidate));
            }
        }
    }
    
    return false;
}

void solve() {
    
    if (check()) std::cout << 1;
    else std::cout << 0;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

