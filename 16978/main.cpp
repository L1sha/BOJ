#include "bits/stdc++.h"


constexpr int N_MAX = 100'001, M_MAX = 100'000;

int N, M, Q, I, J, K, q1Cnt, q2Cnt;

std::array<int, N_MAX> A;
std::array<long long, 4 * N_MAX> segTree;
std::array<std::pair<int, int>, M_MAX> q1;
std::array<std::pair<std::pair<int, int>, std::pair<int, int>>, M_MAX> q2;

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) {
        
        segTree[cursor] = A[l];
    }
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = segTree[cursor * 2] + segTree[cursor * 2 + 1];
    }
}

void segUpdate(const int& target, const int& value, int cursor = 1, int l = 1, int r = N) {
    
    if (l > target || r < target) {
        
        return;
    }
    else if (l == r) {
        
        segTree[cursor] = value;
    }
    else {
        
        segUpdate(target, value, cursor * 2, l, l + (r - l) / 2);
        segUpdate(target, value, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = segTree[cursor * 2] + segTree[cursor * 2 + 1];
    }
}

long long segQuery(const int& ql, const int& qr, int cursor = 1, int l = 1, int r = N) {
    
    if (l > qr || r < ql) {
        
        return 0;
    }
    else if (l >= ql && r <= qr) {
        
        return segTree[cursor];
    }
    else {
        
        return segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2) + segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void solve() {
    
    segInit();
    
    std::vector<long long> res(q2Cnt);
    
    std::sort(q2.begin(), q2.begin() + q2Cnt);
    
    int q1Idx = 0;
    
    for (int q2Idx = 0; q2Idx < q2Cnt; ++q2Idx) {
        
        while (q1Idx < q2[q2Idx].first.first) {
            
            segUpdate(q1[q1Idx].first, q1[q1Idx].second);
            q1Idx++;
        }
        
        res[q2[q2Idx].first.second] = segQuery(q2[q2Idx].second.first, q2[q2Idx].second.second);
    }
    
    for (const auto& el : res) {
        
        std::cout << el << '\n';
    }
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> A[idx];
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> Q;
        
        switch (Q) {
            
            case 1:
            
            std::cin >> q1[q1Cnt].first >> q1[q1Cnt++].second;
            
            break;
            
            case 2:
            
            q2[q2Cnt].first.second = q2Cnt;
            std::cin >> q2[q2Cnt].first.first >> q2[q2Cnt].second.first >> q2[q2Cnt++].second.second;
            
            break;
        }
    }
    
    solve();
    
    return 0;
}

