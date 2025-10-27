#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;

int N, MAX;

std::array<std::pair<int, int>, N_MAX> rectangles;
std::array<std::vector<int>, N_MAX * 2> in;
std::array<int, N_MAX * 2> intersect;
std::array<int, N_MAX * 8> segTree, lazy;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    std::vector<std::pair<int, int>> toSort(N * 2);
    
    for (int trash, input, idx = 0; idx < N; ++idx) {
        
        std::cin >> trash >> input;
        
        toSort[idx * 2] = {input, idx + N_MAX};
        
        std::cin >> trash >> input;
        
        toSort[idx * 2 + 1] = {input, idx};
    }
    
    std::sort(toSort.begin(), toSort.end());
    
    int prev = toSort[0].first, cnt = 0, toBeRemoved = 0;
    
    for (auto& [yCoord, idx] : toSort) {
        
        if (yCoord != prev) {
            
            prev = yCoord;
            cnt++;
            
            intersect[cnt] = intersect[cnt - 1] - toBeRemoved;
            toBeRemoved = 0;
        }
        
        if (idx < N_MAX) {
            
            rectangles[idx].first = cnt;
            in[cnt].push_back(idx);
            intersect[cnt]++;
        }
        else {
            
            rectangles[idx % N_MAX].second = cnt;
            toBeRemoved++;
        }
    }
    
    MAX = cnt;
}

void segInit(int cursor = 1, int l = 0, int r = MAX) {
    
    if (l == r) segTree[cursor] = intersect[l];
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = std::max(segTree[cursor * 2], segTree[cursor * 2 + 1]);
    }
}

void lazyUpdate(const int& cursor, const int& l, const int& r) {
    
    if (lazy[cursor] != 0) {
        
        segTree[cursor] -= lazy[cursor];
        
        if (l != r) {
            
            lazy[cursor * 2] += lazy[cursor];
            lazy[cursor * 2 + 1] += lazy[cursor];
        }
        
        lazy[cursor] = 0;
    }
}

void segUpdate(const int& ql, const int& qr, int cursor = 1, int l = 0, int r = MAX) {
    
    lazyUpdate(cursor, l, r);
    
    if (r < ql || l > qr) return;
    else if (r <= qr && l >= ql) {
        
        segTree[cursor]--;
        
        if (l != r) {
            
            lazy[cursor * 2]++;
            lazy[cursor * 2 + 1]++;
        }
    }
    else {
        
        segUpdate(ql, qr, cursor * 2, l, l + (r - l) / 2);
        segUpdate(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = std::max(segTree[cursor * 2], segTree[cursor * 2 + 1]);
    }
}

void solve() {
    
    segInit();
    
    int res = -1;
    
    for (int idx = 0; idx <= MAX; ++idx) {
        
        for (const int& toRemove : in[idx]) {
            
            segUpdate(rectangles[toRemove].first, rectangles[toRemove].second);
        }
        
        res = std::max(res, intersect[idx] + segTree[1]);
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

