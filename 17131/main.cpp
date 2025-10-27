#include "bits/stdc++.h"


using intPair = std::pair<int, int>;
using Node = std::pair<int, intPair>;

constexpr int N_MAX = 2e5, PRIME = 1e9 + 7;

int N, X, Y;
long long res;

std::array<intPair, N_MAX> stars;
std::array<Node, 4 * N_MAX> segTree;

Node findParent(const Node& left, const Node& right) {
    
    if (left.first < right.first) {
        
        return {left.first, {left.second.first + right.second.first, left.second.second}};
    }
    else if (left.first > right.first) {
        
        return {right.first, {left.second.first + right.second.first, right.second.second}};
    }
    return {left.first, {left.second.first + right.second.first, left.second.second + right.second.second}};
}

Node segInit(int cursor, int l, int r) {
    
    if (l == r) {
        
        return segTree[cursor] = {stars[l].second, {1, 1}};
    }
    
    auto left = segInit(cursor * 2, l, l + (r - l) / 2);
    auto right = segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    
    return segTree[cursor] = findParent(left, right);
}

Node segFind(int cursor, int l, int r, const int& target, int& ans) {
    
    if (l == r) {
        
        ans = l;
        
        return segTree[cursor] = {N_MAX + 1, {0, 0}};
    }
    
    if (segTree[cursor * 2].first == target) {
        
        auto left = segFind(cursor * 2, l, l + (r - l) / 2, target, ans);
        const auto& right = segTree[cursor * 2 + 1];
        
        return segTree[cursor] = findParent(left, right);
    }
    else {
        
        const auto& left = segTree[cursor * 2];
        auto right = segFind(cursor * 2 + 1, l + (r - l) / 2 + 1, r, target, ans);
        
        return segTree[cursor] = findParent(left, right);
    }
}

int segCount(int cursor, int l, int r, const int& ql, const int& qr) {
    
    if (r < ql || l > qr) {
        
        return 0;
    }
    
    if (r <= qr && l >= ql) {
        
        return segTree[cursor].second.first;
    }
    
    return segCount(cursor * 2, l, l + (r - l) / 2, ql, qr) + segCount(cursor * 2 + 1, l + (r - l) / 2 + 1, r, ql, qr);
}

Node segCountDuplicate(int cursor, int l, int r, const int& ql, const int& qr) {
    
    if (r < ql || l > qr) {
        
        return {N_MAX + 1, {0, 0}};
    }
    
    if (r <= qr && l >= ql) {
        
        return segTree[cursor];
    }
    
    auto left = segCountDuplicate(cursor * 2, l, l + (r - l) / 2, ql, qr);
    auto right = segCountDuplicate(cursor * 2 + 1, l + (r - l) / 2 + 1, r, ql, qr);
    
    return findParent(left, right);
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> stars[idx].first >> stars[idx].second;
    }
    
    std::sort(stars.begin(), stars.begin() + N);
    
    segInit(1, 0, N - 1);
    
    int target, ans, ql, qr;
    long long res = 0, left, right;
    
    for (int idx = 0; idx < N; ++idx) {
        
        target = segTree[1].first;
        
        segFind(1, 0, N - 1, target, ans);
        
        ql = 0;
        qr = std::distance(stars.begin(), std::lower_bound(stars.begin(), stars.begin() + N, std::make_pair(stars[ans].first, -N_MAX))) - 1;
        
        if (qr == -1) {
            
            continue;
        }
        
        left = segCount(1, 0, N - 1, ql, qr);
        
        ql = std::distance(stars.begin(), std::upper_bound(stars.begin(), stars.begin() + N, std::make_pair(stars[ans].first, N_MAX)));
        qr = N - 1;
        
        if (ql == N) {
            
            continue;
        }
        
        right = segCount(1, 0, N - 1, ql, qr);
        
        Node temp = segCountDuplicate(1, 0, N - 1, ql, qr);
        
        if (temp.first == target) {
            
            right -= temp.second.second;
        }
        
        res += left * right;
        res %= PRIME;
    }
    
    std::cout << res;
    
    return 0;
}