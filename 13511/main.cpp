#include "bits/stdc++.h"


constexpr int N_MAX = 100'001, logN_MAX = std::ceil(std::log2(N_MAX));

int N, U, V, W, M, Q, K;

std::array<std::vector<std::pair<int, int>>, N_MAX> adjL;
std::array<std::array<std::pair<long long, int>, logN_MAX>, N_MAX> sparse;
std::array<int, N_MAX> rank;
std::array<int, logN_MAX> pow2;

constexpr void fillPow2() {
    
    pow2[0] = 1;
    
    for (int idx = 1; idx < logN_MAX; ++idx) {
        
        pow2[idx] = pow2[idx - 1] * 2;
    }
}

void DFS(int cursor, int parent, int dist) {
    
    rank[cursor] = rank[parent] + 1;
    sparse[cursor][0] = {dist, parent};
    
    for (int idx = 1; idx < logN_MAX; ++idx) {
        
        const auto& [prevDist, prev] = sparse[cursor][idx - 1];
        
        if (prev == 0) {
            
            break;
        }
        
        sparse[cursor][idx] = {prevDist + sparse[prev][idx - 1].first, sparse[prev][idx - 1].second};
    }
    
    for (const auto& [nextDist, next] : adjL[cursor]) {
        
        if (next != parent) {
            
            DFS(next, cursor, nextDist);
        }
    }
}

long long findDist() {
    
    long long Udist = 0, Vdist = 0;
    
    if (rank[U] != rank[V]) {
    
        if (rank[U] < rank[V]) {
            
            std::swap(U, V);
        }
        
        for (int idx = logN_MAX - 1; idx >= 0; --idx) {
            
            if (rank[sparse[U][idx].second] >= rank[V]) {
                
                Udist += sparse[U][idx].first;
                U = sparse[U][idx].second;
            }
        }
    }
    
    if (U == V) {
        
        return Udist;
    }
    
    for (int idx = logN_MAX - 1; idx >= 0; --idx) {
        
        if (sparse[U][idx].second != sparse[V][idx].second) {
            
            Udist += sparse[U][idx].first;
            U = sparse[U][idx].second;
            
            Vdist += sparse[V][idx].first;
            V = sparse[V][idx].second;    
        }
    }
    
    return Udist + sparse[U][0].first + Vdist + sparse[V][0].first;
}

int find(int cursor, int dist) {
    
    int cnt = 0;
    
    while (dist) {
        
        if (dist & 1) {
            
            cursor = sparse[cursor][cnt].second;
        }
        
        cnt++;
        dist /= 2;
    }
    
    return cursor;
}

int findK() {
    
    if (--K == 0) {
        
        return U;
    }
    
    int Usave = U, Vsave = V;
    long long Udist = 0, Vdist = 0;
    
    if (rank[U] < rank[V]) {
        
        for (int idx = logN_MAX - 1; idx >= 0; --idx) {
            
            if (rank[sparse[V][idx].second] >= rank[U]) {
                
                Vdist += pow2[idx];
                V = sparse[V][idx].second;
            }
        }
    }
    else if (rank[U] > rank[V]) {
        
        for (int idx = logN_MAX - 1; idx >= 0; --idx) {
            
            if (rank[sparse[U][idx].second] >= rank[V]) {
                
                Udist += pow2[idx];
                U = sparse[U][idx].second;
            }
        }
    }
    
    if (K <= Udist) {
        
        return find(Usave, K);
    }
    
    if (U != V) {
    
        for (int idx = logN_MAX - 1; idx >= 0; --idx) {
            
            if (sparse[U][idx].second != sparse[V][idx].second) {
                
                Udist += pow2[idx];
                U = sparse[U][idx].second;
                
                Vdist += pow2[idx];
                V = sparse[V][idx].second;    
            }
        }
        
        Udist++;
        Vdist++;
    }
    
    if (K <= Udist) {
        
        return find(Usave, K);
    }
    else {
        
        return find(Vsave, Udist + Vdist - K);
    }
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    fillPow2();
    
    std::cin >> N;
    
    for (int idx = 1; idx < N; ++idx) {
        
        std::cin >> U >> V >> W;
        
        adjL[U].push_back({W, V});
        adjL[V].push_back({W, U});
    }
    
    DFS(1, 0, 0);
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> Q;
        
        switch (Q) {
            
            case 1:
            
            std::cin >> U >> V;
            std::cout << findDist() << '\n';
            break;
            
            case 2:
            
            std::cin >> U >> V >> K;
            std::cout << findK() << '\n';
            break;
        }
    }
    
    return 0;
}

