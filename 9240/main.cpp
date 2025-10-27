#include "bits/stdc++.h"


using Point = std::pair<long long, long long>;

constexpr int N_MAX = 100'000;

int N;
Point minPt;

std::array<Point, N_MAX> pts;
std::array<std::array<bool, 2001>, 2001> duplicate;

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

Point make_vec(const int& idx, const std::vector<Point>& convexHull) {
    
    int sz = convexHull.size();
    
    return {convexHull[(idx + 1) % sz].first - convexHull[idx % sz].first, convexHull[(idx + 1) % sz].second - convexHull[idx % sz].second};
}

bool newCCW(const Point& A, const Point& B) {
    
    long long judge = A.first * B.second - A.second * B.first;
    
    if (judge > 0) {
        
        return true;
    }
    else {
        
        return false;
    }
}

long long dist(const int& idx1, const int& idx2, const std::vector<Point>& convexHull) {
    
    const Point& A = convexHull[idx1];
    const Point& B = convexHull[idx2 % convexHull.size()];
    
    return (A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second);
}

long double solve() {

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
    
    int maxIdx1, maxIdx2;
    
    if (sz == 1) {
        
        return 0;
    }
    else if (sz == 2) {
        
        maxIdx1 = 0;
        maxIdx2 = 1;
        
        return sqrtl(dist(maxIdx1, maxIdx2, convexHull));
    }
    else {
        
        int base = 0, rot = 1;
        Point baseVec, rotVec = make_vec(1, convexHull);
        long long maxDist = 0, temp;
        
        while (base != sz) {
            
            baseVec = make_vec(base, convexHull);
            
            if ((temp = dist(base, rot, convexHull)) > maxDist) {
                
                maxDist = temp;
            }
            
            while (newCCW(baseVec, rotVec)) {
                
                rotVec = make_vec(++rot, convexHull);
                
                if ((temp = dist(base, rot, convexHull)) > maxDist) {
                
                    maxDist = temp;
                }
            }
            
            base++;
        }
        
        return sqrtl(maxDist);
    }
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(8);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> pts[idx].first >> pts[idx].second;
        
        if (duplicate[pts[idx].first + 1000][pts[idx].second + 1000]) {
            
            idx--;
            N--;
        }
        else {
            
            duplicate[pts[idx].first + 1000][pts[idx].second + 1000] = true;
        }
    }
    
    std::cout << solve();
    
    return 0;
}