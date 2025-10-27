#include "bits/stdc++.h"

constexpr int N_MAX = 100'001, LOGN_MAX = ceil(log2(N_MAX)) + 1;

int N;

std::array<std::vector<int>, N_MAX> adjL;
std::array<int, N_MAX> nodeHeight;
std::array<std::array<int, LOGN_MAX>, N_MAX> nodeParent;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int from, to, idx = 0; idx < N - 1; ++idx) {
        
        std::cin >> from >> to;
        adjL[from].push_back(to);
        adjL[to].push_back(from);
    }
}

void DFS(int cursor = 1, int parent = 0, int height = 1) {
    
    nodeHeight[cursor] = height;
    nodeParent[cursor][0] = parent;
    for (int idx = 1; idx < LOGN_MAX; ++idx) {
        
        if (nodeParent[nodeParent[cursor][idx - 1]][idx - 1] == 0) break;
        nodeParent[cursor][idx] = nodeParent[nodeParent[cursor][idx - 1]][idx - 1];
    }
    
    for (const auto& next : adjL[cursor]) {
        
        if (next != parent) {
            
            DFS(next, cursor, height + 1);
        }
    }
}

std::tuple<int, int, int> findLCA(int left, int right) {
    
    int distL = 0, distR = 0;
    
    if (nodeHeight[left] != nodeHeight[right]) {
        
        bool swapped = false;
        
        if (nodeHeight[left] < nodeHeight[right]) {
            
            std::swap(left, right);
            swapped = true;
        }
        
        for (int idx = LOGN_MAX - 1; idx >= 0; --idx) {
            
            if (nodeHeight[nodeParent[left][idx]] >= nodeHeight[right]) {
                
                distL += (1 << idx);
                left = nodeParent[left][idx];
            }
        }
        
        if (swapped) {
            
            std::swap(left, right);
            std::swap(distL, distR);
        }
    }
    
    if (left == right) return {left, distL, distR};
    
    for (int idx = LOGN_MAX - 1; idx >= 0; --idx) {
        
        if (nodeParent[left][idx] != nodeParent[right][idx]) {
            
            distL += (1 << idx);
            left = nodeParent[left][idx];
            
            distR += (1 << idx);
            right = nodeParent[right][idx];
        }
    }
    
    return {nodeParent[left][0], distL + 1, distR + 1};
}

int findParent(int cursor, int dist) {
    
    for (int idx = LOGN_MAX - 1; idx >= 0; --idx) {
        
        if (dist >= (1 << idx)) {
            
            dist -= (1 << idx);
            cursor = nodeParent[cursor][idx];
        }
    }
    
    return cursor;
}

void solve() {
    
    DFS();
    
    int Q, A, B, C;
    
    std::cin >> Q;
    
    while (Q--) {
        
        std::cin >> A >> B >> C;
        
        auto [LCA_AB, dist_AB_A, dist_AB_B] = findLCA(A, B);
        auto [LCA_BC, dist_BC_B, dist_BC_C] = findLCA(B, C);
        auto [LCA_CA, dist_CA_C, dist_CA_A] = findLCA(C, A);
        
        if (LCA_AB == LCA_BC) {
            
            if (LCA_BC == LCA_CA) {
                
                int max = std::max(std::max(dist_AB_A, dist_BC_B), dist_CA_C),
                    min = std::min(std::min(dist_AB_A, dist_BC_B), dist_CA_C),
                    mid = dist_AB_A + dist_BC_B + dist_CA_C - max - min;
                
                if (mid == min && (max + min) % 2 == 0) {
                    
                    if (dist_AB_A == max) std::cout << findParent(A, (max + min) / 2);
                    else if (dist_BC_B == max) std::cout << findParent(B, (max + min) / 2);
                    else std::cout << findParent(C, (max + min) / 2);
                }
                else std::cout << -1;
                
                std::cout << '\n';
                continue;
            }
            else {
                
                // swap(B, C) -> LCA_BC = LCA_CA
                
                std::swap(B, C);
                std::swap(LCA_AB, LCA_CA);
                std::swap(dist_AB_A, dist_CA_A);
                std::swap(dist_AB_B, dist_CA_C);
                std::swap(dist_BC_B, dist_BC_C);
            }
        }
        else if (LCA_CA == LCA_AB) {
            
            // swap(A, C) => LCA_BC = LCA_CA
            
            std::swap(A, C);
            std::swap(LCA_AB, LCA_BC);
            std::swap(dist_AB_A, dist_BC_C);
            std::swap(dist_AB_B, dist_BC_B);
            std::swap(dist_CA_C, dist_CA_A);
        }
        else {} // this case, LCA_BC = LCA_CA assured
        
        if (dist_AB_A == dist_AB_B) {
            
            if (dist_AB_A <= dist_CA_A + dist_CA_C - dist_AB_A
                && (dist_CA_A + dist_CA_C) % 2 == 0) {
                
                if (dist_CA_A > dist_CA_C) std::cout << findParent(A, (dist_CA_A + dist_CA_C) / 2);
                else std::cout << findParent(C, (dist_CA_A + dist_CA_C) / 2);
            }
            else {
                
                std::cout << -1;
            }
        }
        else {
            
            if (dist_AB_A < dist_AB_B) {
                
                // swap (A, B)
                
                std::swap(A, B);
                std::swap(LCA_BC, LCA_CA);
                std::swap(dist_BC_B, dist_CA_A);
                std::swap(dist_BC_C, dist_CA_C);
                std::swap(dist_AB_A, dist_AB_B);
            }
            
            if (dist_AB_B == dist_BC_B + dist_BC_C - dist_AB_B
                && (dist_AB_A + dist_AB_B) % 2 == 0) {
                
                std::cout << findParent(A, (dist_AB_A + dist_AB_B) / 2);
            }
            else {
                
                std::cout << -1;
            }
        }
        
        std::cout << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}