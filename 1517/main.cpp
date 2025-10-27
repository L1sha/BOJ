#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N;
long long res;
std::array<intPair, 500'000> nums;
std::array<int, 2'000'000> segTree;

int insert(int cursor, int l, int r, const int& target) {
    
    if (l > target || r < target) {
        
        return segTree[cursor];
    }
    
    if (l == r) {
        
        return segTree[cursor] = 1;
    }
    
    return segTree[cursor] = insert(cursor * 2, l, l + (r - l) / 2, target) + insert(cursor * 2 + 1, l + (r - l) / 2 + 1, r, target);
}

int query(int cursor, int l, int r, const int& target) {
    
    if (l > target) {
        
        return 0;
    }
    
    if (r <= target) {
        
        return segTree[cursor];   
    }
    
    return query(cursor * 2, l, l + (r - l) / 2, target) + query(cursor * 2 + 1, l + (r - l) / 2 + 1, r, target);
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> nums[idx].first;
        nums[idx].second = idx;
    }
    
    std::sort(nums.begin(), nums.begin() + N);
    
    for (int idx = N - 1; idx >= 0; --idx) {
        
        res += (idx - nums[idx].second + query(1, 0, N - 1, nums[idx].second));
        insert(1, 0, N - 1, nums[idx].second);
    }
    
    std::cout << res;
    
    return 0;
}

