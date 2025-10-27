#include "bits/stdc++.h"


int N, K;
std::bitset<100'001> used;
std::array<int, 100'001> BIT;

void update(int cursor, int value) {
    
    while (cursor <= N) {
        
        BIT[cursor] += value;
        cursor += (cursor & -cursor);
    }
}

int query(int cursor) {
    
    int res = 0;
    
    while (cursor > 0) {
        
        res += BIT[cursor];
        cursor -= (cursor & -cursor);
    }
    
    return res;
}

int find(int target) {
    
    int l = 0, r = N, mid, q;
    
    while (r - l > 1) {
        
        mid = (l + r) / 2;
        q = query(mid);
        
        if (q > target) {
            
            r = mid;
        }
        else if (q == target) {
            
            if (used[mid]) {
                
                r = mid;
            }
            else {
                
                return mid;
            }
        }
        else {
            
            l = mid;
        }
    }
    
    return r;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        update(idx, 1);
    }
    
    int cursor = K, res;
    
    used[K] = true;
    update(K, -1);
    
    std::cout << '<' << K;
    
    for (int remaining = N - 1; remaining > 0; --remaining) {
        
        cursor = (cursor + (K - 1) + (remaining - 1)) % remaining + 1;
        
        res = find(cursor);
        
        used[res] = true;
        update(res, -1);
        
        std::cout << ", " << res;
    }
    
    std::cout << '>';
    
    return 0;
}

