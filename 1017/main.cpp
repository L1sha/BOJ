#include "bits/stdc++.h"


constexpr int N_MAX = 50, SUM_MAX = 2000;

int N;

std::array<int, N_MAX> nums;
std::array<bool, SUM_MAX> isPrime;
std::array<std::vector<int>, N_MAX> primePair;
std::array<int, N_MAX> occupied;
std::bitset<N_MAX> visited;

void findPrime() {
    
    std::fill(isPrime.begin() + 2, isPrime.end(), true);
    
    for (int idx = 2; idx < SUM_MAX; ++idx) {
        
        if (isPrime[idx]) {
            
            for (int idx2 = idx * 2; idx2 < SUM_MAX; idx2 += idx) {
                
                isPrime[idx2] = false;
            }
        }
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        // nums[0] is not included for binary matching
        for (int idx2 = 1; idx2 < N; ++idx2) {
            
            if (idx != idx2 && isPrime[nums[idx] + nums[idx2]]) primePair[idx].push_back(idx2);
        }
    }
}

int DFS(const int& cursor, const int& banned) {
    
    for (const auto& next : primePair[cursor]) {
        
        if (!visited[next] && next != banned) {
            
            visited[next] = true;
            
            if (occupied[next]) {
                
                if (DFS(occupied[next], banned)) {
                    
                    occupied[next] = cursor;
                    return 1;
                }
            }
            else {
                
                occupied[next] = cursor;
                return 1;
            }
        }
    }
    
    return 0;
}

int binaryMatching(int banned) {
    
    std::fill(occupied.begin(), occupied.begin() + N, 0);
    
    int res = 0;
    
    for (int idx = 1; idx < N; ++idx) {
        
        if (idx != banned) {
            
            visited.reset();
            
            res += DFS(idx, banned);
        }
    }
    
    return res;
}

void solve() {
    
    findPrime();
    
    std::vector<int> res;
    res.reserve(primePair[0].size());
    
    for (const auto& candidate : primePair[0]) {
        
        if (binaryMatching(candidate) == N - 2) res.push_back(nums[candidate]);
    }
    
    if (res.empty()) std::cout << -1;
    else {
        
        std::sort(res.begin(), res.end());
        
        for (const auto& el : res) std::cout << el << ' ';
    }    
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> nums[idx];
    
    solve();
    
    return 0;
}

