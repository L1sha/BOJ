#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M, A, B, C;

std::array<intPair, 4'000'004> segTree;
std::array<int, 1'000'001> nums;



intPair init(int idx, int l, int r) {
    
    if (l == r) {
        
        return segTree[idx] = {nums[l], l};
    }
    
    return segTree[idx] = std::min(init(idx * 2, l, l + (r - l) / 2), init(idx * 2 + 1, l + (r - l) / 2 + 1, r));
}

intPair update(int idx, int l, int r) {
    
    if (B < l || B > r) {
        
        return segTree[idx];
    }
    
    if (l == r) {
        
        return segTree[idx] = {C, l};
    }
    
    return segTree[idx] = std::min(update(idx * 2, l, l + (r - l) / 2), update(idx * 2 + 1, l + (r - l) / 2 + 1, r));
}

intPair query(int idx, int l, int r) {
    
    if (C < l || B > r) {
        
        return {INT_MAX, -1};
    }
    
    if (B <= l && C >= r) {
        
        return segTree[idx];
    }
    
    return std::min(query(idx * 2, l, l + (r - l) / 2), query(idx * 2 + 1, l + (r - l) / 2 + 1, r));
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> nums[idx];
    }
    
    init(1, 1, N);
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> A >> B >> C;
        
        switch (A) {
            
            case 1 :
                
                update(1, 1, N);
                
                break;
                
            case 2 :
                
                std::cout << query(1, 1, N).second << '\n';
                
                break;
        }
    }
    
    return 0;
}

