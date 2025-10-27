#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N;

std::array<int, N_MAX> A, S;
std::array<std::pair<int, int>, N_MAX * 4> segTree, minmax;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> A[idx];
        S[idx] = S[idx - 1] + A[idx];
    }
}

void minmaxSegInit(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) minmax[cursor] = {l, r};
    
    else {
        
        minmaxSegInit(cursor * 2, l, l + (r - l) / 2);
        minmaxSegInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        if (S[minmax[cursor * 2].first] > S[minmax[cursor * 2 + 1].first]) {
            
            minmax[cursor].first = minmax[cursor * 2 + 1].first;
        }
        else {
            
            minmax[cursor].first = minmax[cursor * 2].first;
        }
        
        if (S[minmax[cursor * 2].second] > S[minmax[cursor * 2 + 1].second]) {
            
            minmax[cursor].second = minmax[cursor * 2].second;
        }
        else {
            
            minmax[cursor].second = minmax[cursor * 2 + 1].second;
        }
    }
}

int minSegQuery(int ql, int qr, int cursor = 1, int l = 1, int r = N) {
    
    if (l < qr || r > ql) return 0;
    
    else if (l >= ql && r <= qr) return minmax[cursor].first;
    
    else {
        
        int left = minSegQuery(ql, qr, cursor * 2, l, l + (r - l) / 2);
        int right = minSegQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        if (!left) return right;
        if (!right) return left;
        if (S[left] > S[right]) return right;
        else return left;
    }
}

int maxSegQuery(int ql, int qr, int cursor = 1, int l = 1, int r = N) {
    
    if (l < qr || r > ql) return 0;
    
    else if (l >= ql && r <= qr) return minmax[cursor].second;
    
    else {
        
        int left = maxSegQuery(ql, qr, cursor * 2, l, l + (r - l) / 2);
        int right = maxSegQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        if (!left) return right;
        if (!right) return left;
        return (S[left] > S[right]) ? left : right;
    }
}

bool myComp(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
    
    if (S[lhs.second] - S[lhs.first - 1] != S[rhs.second] - S[rhs.first - 1]) {
        
        return S[lhs.second] - S[lhs.first - 1] < S[rhs.second] - S[rhs.first - 1] ;
    }
    else {
        
        return lhs.second - lhs.first < rhs.second - rhs.first;
    }
}

std::pair<int, int> merge(const std::pair<int, int>& left, const std::pair<int, int>& right, const int& mid) {
    
    const auto& [l1, r1] = left;
    const auto& [l2, r2] = right;
    
    std::vector<std::pair<int, int>> candidates;
    candidates.push_back(left);
    candidates.push_back(right);
    candidates.push_back({l1, r2});
    
    int l3 = 0, r3 = 0;
    
    if (r1 != mid) {
        
        l3 = minSegQuery(r1, mid - 1) + 1; 
        candidates.push_back({l3, r2});
    }
    
    if (l2 != mid + 1) {
        
        r3 = maxSegQuery(mid + 1, l2 - 1);
        candidates.push_back({l1, r3});
    }
    
    if (l3 && r3) candidates.push_back({l3, r3});
    
    return *max_element(candidates.begin(), candidates.end(), myComp);
}

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) segTree[cursor] = {l, r};
    
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = merge(segTree[cursor * 2], segTree[cursor * 2 + 1], l + (r - l) / 2);
    }
}

std::pair<int, int> segQuery(int ql, int qr, int cursor = 1, int l = 1, int r = N) {
    
    if (l > qr || r < ql) return {0, 0};
    
    else if (l >= ql && r <= qr) return segTree[cursor];
    
    else {
        
        auto left = segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2);
        auto right = segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        if (!left.first) return right;
        if (!right.first) return left;
        return merge(left, right, l + (r - l) / 2);
    }
}

void solve() {
    
    segInit();
    minmaxSegInit();
    
    int M;
    std::cin >> M;
    
    for (int ql, qr; M--; ) {
        
        std::cin >> ql >> qr;
        auto [l, r] = segQuery(ql, qr);
        std::cout << S[r] - S[l - 1] << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

