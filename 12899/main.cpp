#include "bits/stdc++.h"


int N, A, B;
std::array<int, 8'000'008> segTree;

int add(int idx, int l, int r) {
    
    if (B < l || B > r) {
        
        return segTree[idx];
    }
    
    if (l == r) {
        
        return ++segTree[idx];
    }
    
    return segTree[idx] = add(idx * 2, l, l + (r - l) / 2) + add(idx * 2 + 1, l + (r - l) / 2 + 1, r);
}

int find(int idx, int l, int r) {
    
    segTree[idx]--;
    
    if (l == r) {
        
        return l;
    }
    
    if (segTree[idx * 2] < B) {
        
        B -= segTree[idx * 2];
        return find(idx * 2 + 1, l + (r - l) / 2 + 1, r);
    }
    else {
        
        return find(idx * 2, l, l + (r - l) / 2);
    }
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    while (N--) {
        
        std::cin >> A >> B;
        
        switch (A) {
            
            case 1:
            
            add(1, 1, 2'000'000);
            break;
            
            case 2:
            
            std::cout << find(1, 1, 2'000'000) << '\n';
            break;
        }
    }
    
    return 0;
}

