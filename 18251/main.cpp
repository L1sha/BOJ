#include "bits/stdc++.h"

constexpr int myLog2(int N) {
    
    int res = 0;
    while (N > 1) {
        
        ++res;
        N >>= 1;
    }
    return res;
}

constexpr int N_MAX = 262144, H_MAX = myLog2(N_MAX);

int N, H;

std::array<std::array<long long, H_MAX>, H_MAX> max, currentSum;
std::array<int, N_MAX> tree;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    H = myLog2(N + 1);
    for (int idx = 1; idx <= N; ++idx) std::cin >> tree[idx];
}

void DFS(int cursor = 1, int height = 0) {
    
    if (height == H) return;
    
    DFS(cursor * 2, height + 1);
    
    for (int left = 0; left <= height; ++left) {
        
        for (int right = height; right < H; ++right) {
            
            if (tree[cursor] > 0) {
                
                currentSum[left][right] += tree[cursor];
                max[left][right] = std::max(max[left][right], currentSum[left][right]);
            }
            else {
                
                if (currentSum[left][right] + tree[cursor] < 0) currentSum[left][right] = 0;
                else currentSum[left][right] += tree[cursor];
            }
        }
    }
    
    DFS(cursor * 2 + 1, height + 1);
}

void solve() {
    
    DFS();
    
    long long res = 0;
    
    for (int left = 0; left < H; ++left) {
        
        for (int right = left; right < H; ++right) {
            
            res = std::max(res, max[left][right]);
        }
    }
    
    if (res == 0) res = *std::max_element(tree.begin() + 1, tree.begin() + N + 1);
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

