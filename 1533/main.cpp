#include "bits/stdc++.h"


int N, S, E, T;
const int PRIME = 1'000'003;
std::array<std::array<long long, 50>, 50> adj, res, temp;

void matMult(std::array<std::array<long long, 50>, 50>& A, std::array<std::array<long long, 50>, 50>& B) {
    
    for (int row = 0; row < 5 * N; ++row) {
        
        for (int col = 0; col < 5 * N; ++col) {
            
            for (int idx = 0; idx < 5 * N; ++idx) {
                
                temp[row][col] = (temp[row][col] + A[row][idx] * B[idx][col]) % PRIME;
            }
        }
    }
    
    for (int row = 0; row < 5 * N; ++row) {
        
        for (int col = 0; col < 5 * N; ++col) {
            
            A[row][col] = temp[row][col];
            temp[row][col] = 0;
        }
    }
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> S >> E >> T;
    
    for (int idx = 0; idx < N; ++idx) {
        
        for (int t = 0; t < 4; ++t) {
            
            adj[5 * idx + t][5 * idx + t + 1] = 1;
        }
    }
    
    char c;
    
    for (int start = 1; start <= N; ++start) {
        
        for (int end = 1; end <= N; ++end) {
            
            std::cin >> c;
            if (c != '0') {
                
                adj[5 * start - 1][5 * end - (c - '0')] = 1;
            }
        }
    }
    
    for (int idx = 0; idx < 5 * N; ++idx) {
        
        res[idx][idx] = 1;
    }
    
    while (T) {
        
        if (T % 2) {
            
            matMult(res, adj);
        }
        
        T /= 2;
        matMult(adj, adj);
    }
    
    std::cout << res[5 * S - 1][5 * E - 1];
    
    return 0;
}

