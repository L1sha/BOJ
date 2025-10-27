#include "bits/stdc++.h"

constexpr int N_MAX = 10'000;

int N;

struct Point {
    
    long long x, y;
};

std::istream& operator>> (std::istream& is, Point& pt) {
    
    is >> pt.x >> pt.y;
    return is;
}

std::array<Point, N_MAX> pts;
std::array<Point, 3> targets;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> pts[idx];
    for (auto& el : targets) std::cin >> el;
}

bool cross(const Point& pt1, const Point& pt2, const Point& pt3, const Point& pt4) {
    
    auto [X1, Y1] = pt1;
    auto [X2, Y2] = pt2;
    auto [X3, Y3] = pt3;
    auto [X4, Y4] = pt4;
    
    bool res = false;
    constexpr long long zero = 0;
    
    if (X1 > X2) { std::swap(X1, X2); std::swap(Y1, Y2); } 
    
    X2 -= X1;   // X2 >= 0
    X3 -= X1;
    X4 -= X1;
    Y2 -= Y1;
    Y3 -= Y1;
    Y4 -= Y1;
    X1 = 0;
    Y1 = 0;
    
    long long a = Y2, b = - X2; // P1, P2 : ax + by = 0
    
    long long judge3 = a * X3 + b * Y3, judge4 = a * X4 + b * Y4;
    
    if (!judge3 && !judge4) {   //  both P3 & P4 are on the line
        
        if (X2 == 0){   // line x = 0
            
            if ((Y3 >= std::min(zero, Y2) && Y3 <= std::max(zero, Y2)) || (Y4 >= std::min(zero, Y2) && Y4 <= std::max(zero, Y2))) res = true;
            
            else if ((Y3 < std::min(zero, Y2) && Y4 > std::max(zero, Y2)) || (Y3 > std::max(zero, Y2) && Y4 < std::min(zero, Y2))) res = true;
        }
        
        else {      // X2 > 0
            
            if ((X3 >= 0 && X3 <= X2) || (X4 >= 0 && X4 <= X2)) res = true;
            
            else if ((X3 < 0 && X4 > X2) || (X3 > X2 && X4 < 0)) res = true;
        }
        
    }
    
    else if (!judge3 || !judge4) {       // only one of P3 & P4 is on the line
        
        if (!judge4) { std::swap(X3, X4); std::swap(Y3, Y4); }  // P3 is on the line
        
        if (X2 == 0) {  // line x = 0
            
            if (Y3 >= std::min(zero, Y2) && Y3 <= std::max(zero, Y2)) res = true;
        }
        
        else {  // X2 > 0
            
            if (X3 >= 0 && X3 <= X2) res = true;
        }
    }
    
    else if ((judge3 > 0 && judge4 < 0) || (judge3 < 0 && judge4 > 0)) {    // P3, P4 is on different side
        
        if (X3 > X4) { std::swap(X3, X4); std::swap(Y3, Y4); }
        X4 -= X3; // X4 >= 0
        X1 -= X3;
        X2 -= X3;
        Y4 -= Y3;
        Y1 -= Y3;
        Y2 -= Y3;
        X3 = 0;
        Y3 = 0;
        
        long long c = Y4, d = -X4; // P3, P4 : cx + dy = 0
        
        long long judge1 = c * X1 + d * Y1, judge2 = c * X2 + d * Y2;
        
        if (!judge1 || !judge2) {   // at least one of P1, P2 is on the line
            
            res = true;
        }
        else if ((judge1 > 0 && judge2 < 0) || (judge1 < 0 && judge2 > 0)) {     // P1, P2 is on different side
        
            res = true;
        }
    }

    return res;
}


void solve() {
    
    for (const auto& pt1 : targets) {
        
        int cnt = 0;
        const auto& [x, y] = pt1;
        Point pt2 = {1'000'000'001, pt1.y + 1};
        
        for (int idx = 0; idx < N; ++idx) {
            
            const auto& [x1, y1] = pts[idx];
            const auto& [x2, y2] = pts[(idx + 1) % N];
            
            if ((y2 - y1) * (x - x1) + (x1 - x2) * (y - y1) == 0) { // on-line
                
                if (y >= std::min(y1, y2) && y <= std::max(y1, y2)
                && x >= std::min(x1, x2) && x <= std::max(x1, x2)) {
                    
                    cnt = 1;
                    break;
                }
            }
            
            if (cross(pt1, pt2, pts[idx], pts[(idx + 1) % N])) ++cnt;
        }
        
        if (cnt & 1) std::cout << "1\n";
        else std::cout << "0\n";
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}