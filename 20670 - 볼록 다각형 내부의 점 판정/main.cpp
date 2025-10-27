// https://restudycafe.tistory.com/406

#include "bits/stdc++.h"

constexpr int N_MAX = 10'000, K_MAX = 300'000;
constexpr long long NONE = 1'000'000'001;

int N, M, K;

struct Point{
    
    long long x, y;
};

struct Line{
    
    // ax + by + c = 0, b >= 0
    
    long long startX, a, b, c;
    
    bool operator<(const Line& rhs) const {
        
        return startX < rhs.startX;
    }
};

std::istream& operator>>(std::istream& is, Point& pt) {
    
    is >> pt.x >> pt.y;
    return is;
}

std::array<std::array<Point, N_MAX>, 2> convex;
std::array<Point, K_MAX> sign;

std::array<std::vector<Line>, 2> rightLine, leftLine;
std::array<long long, 2> leftEndX{NONE, NONE}, rightEndX = {-NONE, -NONE};


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> K;
    
    rightLine[0].reserve(N);
    leftLine[0].reserve(N);
    rightLine[1].reserve(M);
    leftLine[1].reserve(M);
    
    for (int idx = 0; idx < N; ++idx) std::cin >> convex[0][idx];
    for (int idx = 0; idx < M; ++idx) std::cin >> convex[1][idx];
    for (int idx = 0; idx < K; ++idx) std::cin >> sign[idx];
}

void solve() {
    
    // (y2 - y1)(x - x1) + (x1 - x2)(y - y1) = 0
    
    std::array<int, 2> nodeNum{N, M};
    
    for (int cIdx = 0; cIdx < 2; ++cIdx) {
        
        for (int idx = 0; idx < nodeNum[cIdx]; ++idx) {
            
            auto [x1, y1] = convex[cIdx][idx];
            auto [x2, y2] = convex[cIdx][(idx + 1) % nodeNum[cIdx]];
            
            leftEndX[cIdx] = std::min(leftEndX[cIdx], x1);
            rightEndX[cIdx] = std::max(rightEndX[cIdx], x1);
            
            if (x1 > x2) {
                
                leftLine[cIdx].push_back({x2, y2 - y1, x1 - x2, (y1 - y2) * x1 - (x1 - x2) * y1});
            }
            else if (x1 < x2) {
                
                rightLine[cIdx].push_back({x1, y1 - y2, x2 - x1, (y2 - y1) * x1 - (x2 - x1) * y1});
            }
        }
        
        std::sort(leftLine[cIdx].begin(), leftLine[cIdx].end());
        std::sort(rightLine[cIdx].begin(), rightLine[cIdx].end());
    }
    
    int res = 0;
    
    for (int idx = 0; idx < K; ++idx) {
        
        auto [x, y] = sign[idx];
        
        if (x <= leftEndX[0] || x >= rightEndX[0]) {
            
            ++res;
            continue;
        }
        
        auto it1 = std::upper_bound(rightLine[0].begin(), rightLine[0].end(), Line{x, 0, 0, 0});
        auto [no_use1, a1, b1, c1] = *(it1 - 1);
        
        if (a1 * x + b1 * y + c1 < 0) {
            
            ++res;
            continue;
        }
        
        auto it2 = std::upper_bound(leftLine[0].begin(), leftLine[0].end(), Line{x, 0, 0, 0});
        auto [no_use2, a2, b2, c2] = *(it2 - 1);
        
        if (a2 * x + b2 * y + c2 > 0) {
            
            ++res;
            continue;
        }
        
        if (x <= leftEndX[1] || x >= rightEndX[1]) continue;
        
        auto it3 = std::upper_bound(rightLine[1].begin(), rightLine[1].end(), Line{x, 0, 0, 0});
        auto [no_use3, a3, b3, c3] = *(it3 - 1);
        
        auto it4 = std::upper_bound(leftLine[1].begin(), leftLine[1].end(), Line{x, 0, 0, 0});
        auto [no_use4, a4, b4, c4] = *(it4 - 1);
        
        if (a3 * x + b3 * y + c3 > 0 && a4 * x + b4 * y + c4 < 0) {
            
            ++res;
            continue;
        }
    }
    
    if (res == 0) std::cout << "YES";
    else std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}