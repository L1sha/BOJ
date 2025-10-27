#include "bits/stdc++.h"


constexpr int N_MAX = 1'000'000;

int N, M, K, A, B, C;
long long D;

std::array<long long, N_MAX> nums;
std::array<std::pair<long long, long long>, N_MAX * 4> segTree;

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    if (l == r) {
        
        segTree[cursor].first = nums[l];
        return;
    }
    
    segInit(cursor * 2, l, l + (r - l) / 2);
    segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    
    segTree[cursor].first = segTree[cursor * 2].first + segTree[cursor * 2 + 1].first;
}

void segUpdate(int cursor = 1, int l = 1, int r = N) {
    
    if (l != r) {
        
        segTree[cursor * 2].second += segTree[cursor].second;;
        segTree[cursor * 2 + 1].second += segTree[cursor].second;
    }
    
    segTree[cursor].first += segTree[cursor].second * (r - l + 1);
    segTree[cursor].second = 0;
    
    if (l > C || r < B) {
        
        return;
    }
    
    if (l >= B && r <= C) {
        
        if (l == r) {
            
            segTree[cursor].first += D;
        }
        else {
            
            segTree[cursor].first += (r - l + 1) * D;
            segTree[cursor * 2].second += D;
            segTree[cursor * 2 + 1].second += D;
        }
        
        return;
    }
    
    segUpdate(cursor * 2, l, l + (r - l) / 2);
    segUpdate(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    
    segTree[cursor].first = segTree[cursor * 2].first + segTree[cursor * 2 + 1].first;
}

long long segQuery(int cursor = 1, int l = 1, int r = N) {
    
    if (l != r) {
        
        segTree[cursor * 2].second += segTree[cursor].second;;
        segTree[cursor * 2 + 1].second += segTree[cursor].second;
    }
    
    segTree[cursor].first += segTree[cursor].second * (r - l + 1);
    segTree[cursor].second = 0;
    
    if (l > C || r < B) {
        
        return 0;
    }
    
    if (l >= B && r <= C) {
        
        return segTree[cursor].first;
    }
    
    return segQuery(cursor * 2, l, l + (r - l) / 2) + segQuery(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> K;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> nums[idx];
    }
    
    segInit();
    
    for (int idx = 0; idx < M + K; ++idx) {
        
        std::cin >> A;
        
        switch (A) {
            
            case 1:
            
            std::cin >> B >> C >> D;
            segUpdate();
            
            break;
            
            case 2:
            
            std::cin >> B >> C;
            std::cout << segQuery() << '\n';
            
            break;
        }
    }
    
    return 0;
}

