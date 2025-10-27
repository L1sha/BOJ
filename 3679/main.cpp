#include "bits/stdc++.h"


using LLpair = std::pair<long long, long long>;
using Point = std::pair<LLpair, int>;

int C, N;
LLpair min;
std::array<Point, 2000> pts;

bool CCW(const Point& a, const Point& b) {
    
    if (a.first == min) {
        
        return true;
    }
    
    if (b.first == min) {
        
        return false;
    }
    
    LLpair A = a.first, B = b.first;
    
    A.first -= min.first;
    A.second -= min.second;
    B.first -= min.first;
    B.second -= min.second;
    
    long long judge = A.first * B.second - A.second * B.first;
    
    if (judge > 0) {
        
        return true;
    }
    else if (judge == 0) {
        
        return A.first * A.first + A.second * A.second < B.first * B.first + B.second * B.second;
    }
    else {
        
        return false;
    }
}

void solve() {
    
    min = {10'001, 10'001};
    
    for (int idx = 0; idx < N; ++idx) {
        
        min = std::min(min, pts[idx].first);
    }
    
    std::sort(pts.begin(), pts.begin() + N, CCW);
    
    int cursor = N - 1;
    
    while (true) {
        
        LLpair A = pts[cursor].first, B = pts[cursor - 1].first;
        A.first -= min.first;
        A.second -= min.second;
        B.first -= min.first;
        B.second -= min.second;
        
        if (A.first * B.second - A.second * B.first == 0) {
            
            cursor--;
        }
        else {
            
            break;
        }
    }
    
    std::reverse(pts.begin() + cursor, pts.begin() + N);
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cout << pts[idx].second << ' ';
    }
    
    std::cout << '\n';
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> C;
    
    while (C--) {
        
        std::cin >> N;
        
        for (int idx = 0; idx < N; ++idx) {
            
            std::cin >> pts[idx].first.first >> pts[idx].first.second;
            pts[idx].second = idx;
        }
        
        solve();
    }
    
    return 0;
}