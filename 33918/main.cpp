#include "bits/stdc++.h"

constexpr int N_MAX = 201, M_MAX = 25001;

int N, M, C, D;

std::array<int, N_MAX> B;
std::array<std::array<int, M_MAX>, N_MAX> res;

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> C >> D;
    for (int idx = 0; idx < N; ++idx) std::cin >> B[idx];
}

void solve() {
    
    for (int rem = 1; rem <= C; ++rem) {
        
        for (int t = 0; t < N; ++t) {
            
            std::deque<std::pair<int, int>> deq;
            
            for (int temp = rem; temp < rem + D; temp += C) {
                
                while (!deq.empty() && deq.back().first <= res[t][temp]) {
                    
                    deq.pop_back();
                }
                
                deq.push_back({res[t][temp], temp});
            }
            
            for (int temp = rem; temp <= M; temp += C) {
                
                if (temp + D <= M) {
                    
                    while (!deq.empty() && deq.back().first <= res[t][temp + D]) {
                        
                        deq.pop_back();
                    }
                    
                    deq.push_back({res[t][temp + D], temp + D});
                }
                
                if (deq.front().second < temp - D) deq.pop_front();
                
                res[t + 1][temp] = deq.front().first + M - abs(B[t] - temp);
            }
        }
    }
    
    std::cout << *std::max_element(res[N].begin() + 1, res[N].begin() + 1 + M);
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}