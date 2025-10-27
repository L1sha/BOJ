#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M, A, B;

std::array<intPair, 400'004> segTree;
std::array<int, 100'001> nums;



intPair minMax(intPair a, intPair b) {
    
    return { std::min(a.first, b.first), std::max(a.second, b.second) };
}

intPair init(int idx, int l, int r) {
    
    if (l == r) {
        
        return segTree[idx] = { nums[l], nums[l] };
    }
    
    return segTree[idx] = minMax(init(idx * 2, l, l + (r - l) / 2), init(idx * 2 + 1, l + (r - l) / 2 + 1, r));
}

/*
long long update(int idx, int l, int r) {
    
    if (B < l || B > r) {
        
        return segTree[idx];
    }
    
    if (l == r) {
        
        return segTree[idx] = C;
    }
    
    return segTree[idx] = update(idx * 2, l, l + (r - l) / 2) + update(idx * 2 + 1, l + (r - l) / 2 + 1, r);
}
*/

intPair query(int idx, int l, int r) {
    
    if (B < l || A > r) {
        
        return { INT_MAX, INT_MIN };
    }
    
    if (A <= l && B >= r) {
        
        return segTree[idx];
    }
    
    return minMax(query(idx * 2, l, l + (r - l) / 2), query(idx * 2 + 1, l + (r - l) / 2 + 1, r));
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> nums[idx];
    }
    
    init(1, 1, N);
    
    intPair temp;
    
    while (M--) {
        
        std::cin >> A >> B;
        
        temp = query(1, 1, N);
        std::cout << temp.first << ' ' << temp.second << '\n';
    }
    
    return 0;
}

