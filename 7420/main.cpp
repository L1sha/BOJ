#include "bits/stdc++.h"


using Point = std::pair<long long, long long>;

constexpr int N_MAX = 1000;
const long double PI = 3.141592653589793238462643383279;

int N, L;
Point minPt;

std::array<Point, N_MAX> pts;

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

bool CCW3(const Point & A, const Point& B, const Point& C) {
    
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

long long solve() {

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
    
    sz = convexHull.size();
    
    long double res = sqrtl((convexHull[0].first - convexHull[sz - 1].first) * (convexHull[0].first - convexHull[sz - 1].first) + (convexHull[0].second - convexHull[sz - 1].second) * (convexHull[0].second - convexHull[sz - 1].second));
    
    for (int idx = 1; idx < sz; ++idx) {
        
        res += sqrtl((convexHull[idx].first - convexHull[idx - 1].first) * (convexHull[idx].first - convexHull[idx - 1].first) + (convexHull[idx].second - convexHull[idx - 1].second) * (convexHull[idx].second - convexHull[idx - 1].second));
    }
    
    res += 2 * PI * L;
    
    return res;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> L;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> pts[idx].first >> pts[idx].second;
    }
    
    std::cout << solve();
    
    return 0;
}

