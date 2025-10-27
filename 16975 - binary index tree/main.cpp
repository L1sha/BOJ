#include "bits/stdc++.h"


int N, M, A, prev, ql, qr, k, x;
std::array<long long, 100'001> BIT; // binary index tree

void update(int target, int value) {
    
    while (target <= N) {
        
        BIT[target] += value;
        target += (target & -target);
    }
}

long long query(int target) {
    
    long long res = 0;
    
    while (target > 0) {
        
        res += BIT[target];
        target -= (target & -target);
    }
    
    return res;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> A;
        
        update(idx, A - prev);
        
        prev = A;
    }
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> k;
        
        switch (k) {
            
            case 1:
            
            std::cin >> ql >> qr >> k;
            update(ql, k);
            
            if (qr != N) {
                
                update(qr + 1, -k);
            }
            
            break;
            
            case 2:
            
            std::cin >> x;
            std::cout << query(x) << '\n';
            
            break;
        }
    }
    
    return 0;
}

