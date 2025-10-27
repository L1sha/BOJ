#include "bits/stdc++.h"


int N, M, K, A, B;
long long C;
const int PRIME = 1'000'000'007;

std::array<long long, 4'000'004> segTree;
std::array<long long, 1'000'001> nums;



long long init(int idx, int l, int r) {
    
    if (l == r) {
        
        return segTree[idx] = nums[l];
    }
    
    return segTree[idx] = (init(idx * 2, l, l + (r - l) / 2) * init(idx * 2 + 1, l + (r - l) / 2 + 1, r)) % PRIME;
}

long long update(int idx, int l, int r) {
    
    if (B < l || B > r) {
        
        return segTree[idx];
    }
    
    if (l == r) {
        
        return segTree[idx] = C;
    }
    
    return segTree[idx] = (update(idx * 2, l, l + (r - l) / 2) * update(idx * 2 + 1, l + (r - l) / 2 + 1, r)) % PRIME;
}

long long query(int idx, int l, int r) {
    
    if (C < l || B > r) {
        
        return 1;
    }
    
    if (B <= l && C >= r) {
        
        return segTree[idx];
    }
    
    return (query(idx * 2, l, l + (r - l) / 2) * query(idx * 2 + 1, l + (r - l) / 2 + 1, r)) % PRIME;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> K;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> nums[idx];
    }
    
    init(1, 1, N);
    
    for (int idx = 0; idx < M + K; ++idx) {
        
        std::cin >> A >> B >> C;
        
        switch (A) {
            
            case 1 :
                
                update(1, 1, N);
                
                break;
                
            case 2 :
                
                std::cout << query(1, 1, N) << '\n';
                
                break;
        }
    }
    
    return 0;
}

