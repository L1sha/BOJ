#include "bits/stdc++.h"


int N, input;
long long res;
std::unordered_map<int, int> hash;
std::array<int, 2'000'000> segTree;

int insert(int&& idx, int&& l, int&& r, const int& val) {
    
    if (val < l || val > r) {
        
        return segTree[idx];
    }
    
    if (l == r) {
        
        return segTree[idx] = 1;
    }
    
    return segTree[idx] = insert(idx * 2, std::move(l), l + (r - l) / 2, val) + insert(idx * 2 + 1, l + (r - l) / 2 + 1, std::move(r), val);
}

int query(int&& idx, int&& l, int&&r, const int& val) {
    
    if (r < val) {
        
        return 0;
    }
    
    if (l >= val) {
        
        return segTree[idx];
    }
    
    return query(idx * 2, std::move(l), l + (r - l) / 2, val) + query(idx * 2 + 1, l + (r - l) / 2 + 1, std::move(r), val);
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> input;
        hash[input] = idx;
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> input;
        res += query(1, 0, N - 1, hash[input]);
        insert(1, 0, N - 1, hash[input]);
    }
    
    std::cout << res;
    
    return 0;
}

