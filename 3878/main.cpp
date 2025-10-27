#include "bits/stdc++.h"


using Point = std::pair<long long, long long>;

constexpr int N_MAX = 100;

int T, N, M;
Point minPt;
const long long zero = 0;

std::array<Point, N_MAX> black, white;

bool CCW(const Point& A, const Point& B) {
    
    long long judge = A.first * B.second - A.second * B.first;
    
    if (judge > 0) {
        
        return true;
    }
    else if (judge < 0) {
        
        return false;
    }
    else {
        
        return A.first * A.first + A.second * A.second > B.first * B.first + B.second * B.second;
    }
}

bool CCW2(const Point& A, const Point& B) {
    
    if (A == minPt) {
        
        return true;
    }
    
    if (B == minPt) {
        
        return false;
    }
    
    Point newA, newB;
    
    newA.first = A.first - minPt.first;
    newA.second = A.second - minPt.second;
    newB.first = B.first - minPt.first;
    newB.second = B.second - minPt.second;
    
    return CCW(newA, newB);
}

bool CCW3(const Point& A, const Point& B, const Point& C) {
    
    Point newA, newB;
    
    newA.first = A.first - C.first;
    newA.second = A.second - C.second;
    newB.first = B.first - C.first;
    newB.second = B.second - C.second;
    
    return CCW(newA, newB);
}

bool onSameLine(Point A, Point B) {
    
    A.first -= minPt.first;
    A.second -= minPt.second;
    B.first -= minPt.first;
    B.second -= minPt.second;
    
    return A.first * B.second == A.second * B.first;
}

std::vector<Point> make_convexHull(std::array<Point, N_MAX>& pts, const int& N) {
    
    minPt = *std::min_element(pts.begin(), pts.begin() + N);
    
    std::sort(pts.begin(), pts.begin() + N, CCW2);
    
    std::vector<Point> convexHull;
    int sz; 
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (convexHull.size() >= 2 && onSameLine(pts[idx], convexHull.back())) {
            
            continue;
        }
        
        while ((sz = convexHull.size()) >= 2) {
            
            if (CCW3(pts[idx], convexHull[sz - 1], convexHull[sz - 2])) {
                
                convexHull.pop_back();
            }
            else {
                
                break;
            }
        }
        
        convexHull.push_back(pts[idx]);
    }
    
    return convexHull;
}

bool cross(const Point& P1, const Point& P2, const Point& P3, const Point& P4) {
    
    auto [X1, Y1] = P1;
    auto [X2, Y2] = P2;
    auto [X3, Y3] = P3;
    auto [X4, Y4] = P4;
    
    bool res = false;
    
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
        
        if (X2 == 0) {   // line x = 0
            
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

bool onLine(Point A, Point B, const Point& C) {
    
    A.first -= C.first;
    A.second -= C.second;
    B.first -= C.first;
    B.second -= C.second;
    
    if (A.first * B.first > 0 || A.second * B.second > 0) {
        
        return false;
    }
    
    return A.first * B.second == A.second * B.first;
}

bool inside(const Point& A, const std::vector<Point>& CH) {
    
    Point B, C;
    int sz = CH.size();
    
    for (int idx = 0; idx < sz; ++idx) {
        
        B = {CH[idx].first - A.first, CH[idx].second - A.second};
        C = {CH[(idx + 1) % sz].first - A.first, CH[(idx + 1) % sz].second - A.second};
        
        if (!CCW(B, C)) {
            
            return false;
        }
    }
    
    return true;
}

bool solve() {

    auto bCH = make_convexHull(black, N), wCH = make_convexHull(white, M);
    int bSZ = bCH.size(), wSZ = wCH.size();
    
    if (bSZ == 1) {
        
        if (wSZ == 1) {
            
            return true;
        }
        else {
            
            for (int wIdx = 0; wIdx < wSZ; ++wIdx) {
                
                if (onLine(wCH[wIdx], wCH[(wIdx + 1) % wSZ], bCH[0])) {
                    
                    return false;
                }
            }
        }
    }
    else if (wSZ == 1) {
        
        for (int bIdx = 0; bIdx < bSZ; ++bIdx) {
            
            if (onLine(bCH[bIdx], bCH[(bIdx + 1) % bSZ], wCH[0])) {
                
                return false;
            }
        }
    }
    else {
        
        for (int bIdx = 0; bIdx < bSZ; ++bIdx) {
            
            for (int wIdx = 0; wIdx < wSZ; ++wIdx) {
                
                if (cross(bCH[bIdx], bCH[(bIdx + 1) % bSZ], wCH[wIdx], wCH[(wIdx + 1) % wSZ])) {
                    
                    return false;
                }
            }
        }
    }
    
    if (bSZ > 2) {
        
        if (inside(wCH[0], bCH)) {
            
            return false;
        }
    }
    
    if (wSZ > 2) {
        
        if (inside(bCH[0], wCH)) {
            
            return false;
        }
    }
    
    return true;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> N >> M;
        
        for (int idx = 0; idx < N; ++idx) {
            
            std::cin >> black[idx].first >> black[idx].second;
        }
        
        for (int idx = 0; idx < M; ++idx) {
            
            std::cin >> white[idx].first >> white[idx].second;
        }
        
        if (solve()) {
            
            std::cout << "YES\n";
        }
        else {
            
            std::cout << "NO\n";
        }
    }
    
    return 0;
}

