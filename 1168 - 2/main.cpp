#include "bits/stdc++.h"


int N, K;

std::array<int, 400'004> segTree;

void init(int cursor, int l, int r) {
    
    segTree[cursor] = r - l + 1;
    
    if (l != r) {
        
        init(cursor * 2, l, l + (r - l) / 2);
        init(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

int find(int cursor, int l, int r, int target) {
    
    segTree[cursor]--;
    
    if (l == r) {
        
        return l;
    }
    
    if (segTree[cursor * 2] < target) {
        
        return find(cursor * 2 + 1, l + (r - l) / 2 + 1, r, target - segTree[cursor * 2]);
    }
    
    return find(cursor * 2, l, l + (r - l) / 2, target);
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    init(1, 1, N);
    int cursor = 1;
    
    std::cout << '<';
    
    for (int remaining = N; remaining > 0; --remaining) {
        
        cursor = (cursor + (K - 1) + (remaining - 1)) % remaining + 1;
        
        std::cout << find(1, 1, N, cursor);
        
        if (remaining == 1) {
            
            std::cout << '>';
        }
        else {
            
            std::cout << ", ";
        }
    }
    
    return 0;
}

