#include "bits/stdc++.h"

constexpr int N_MAX = 3000;


struct Gold {
    
    int X, Y;
    long long W;
};

bool xComp (const Gold& lhs, const Gold& rhs) {
    
    if (lhs.X == rhs.X) return lhs.Y < rhs.Y;
    return lhs.X < rhs.X;
}

bool yComp (const Gold& lhs, const Gold& rhs) {
    
    if (lhs.Y == rhs.Y) return lhs.X < rhs.X;
    return lhs.Y < rhs.Y;
}

std::istream& operator>> (std::istream& is, Gold& g) {
    
    is >> g.X >> g.Y >> g.W;
    return is;
}

struct Node {
    
    long long leftMax, rightMax, max, sum;
    bool isEmpty;
    
    void reset() {
        
        leftMax = 0;
        rightMax = 0;
        max = 0;
        sum = 0;
        isEmpty = true;
    }
    
    void merge(const Node& l, const Node& r) {
        
        if (l.isEmpty) *this = r;
        else if (r.isEmpty) *this = l;
        else {
            
            leftMax = std::max(l.leftMax, l.sum + r.leftMax);
            rightMax = std::max(r.rightMax, r.sum + l.rightMax);
            max = std::max(l.max, r.max);
            max = std::max(max, l.rightMax + r.leftMax);
            sum = l.sum + r.sum;
            isEmpty = false;
        }
    }
    
    void leafUpdate(const int& val) {
        
        leftMax += val;
        rightMax += val;
        max += val;
        sum += val;
        isEmpty = false;
    }
};



int N, compN = 0;

std::array<Gold, N_MAX> golds;
std::array<Node, N_MAX * 4> segTree;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> golds[idx];
}

void XCoordCompression() {
    
    std::sort(golds.begin(), golds.begin() + N, xComp);
    
    int prev = golds.front().X - 1;
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (prev != golds[idx].X) {
            
            prev = golds[idx].X;
            ++compN;
        }
        
        golds[idx].X = compN;
    }
}

void segInit(int cursor = 1, int l = 1, int r = compN) {
    
    segTree[cursor].reset();
    
    if (l != r) {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void segUpdate(const int& target, const int& val, int cursor = 1, int l = 1, int r = compN) {
    
    if (l > target || r < target) return;
    else if (l == r) {
        
        segTree[cursor].leafUpdate(val);
    }
    else {
        
        segUpdate(target, val, cursor * 2, l, l + (r - l) / 2);
        segUpdate(target, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor].merge(segTree[cursor * 2], segTree[cursor * 2 + 1]);
    }
}

void solve() {
    
    XCoordCompression();
    
    std::sort(golds.begin(), golds.begin() + N, yComp);
    
    long long res = 0;
    
    for (int startIdx = 0; startIdx < N; ++startIdx) {
        
        segInit();
        
        for (int idx = startIdx; idx < N; ++idx) {
            
            segUpdate(golds[idx].X, golds[idx].W);
            
            while (idx < N - 1 && golds[idx].Y == golds[idx + 1].Y) {
                
                ++idx;
                segUpdate(golds[idx].X, golds[idx].W);
            }
            
            res = std::max(res, segTree[1].max);
        }
        
        while (startIdx < N - 1 && golds[startIdx].Y == golds[startIdx + 1].Y) ++startIdx;
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

