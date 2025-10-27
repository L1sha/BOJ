#include "bits/stdc++.h"


using LLpair = std::pair<long long, long long>;

int N, cnt;
LLpair min;
std::array<LLpair, 100> pts;

bool CCW(const LLpair& A, const LLpair& B) {
    
    if (A.first == 0 && A.second == 0) {
        
        return true;
    }
    
    if (B.first == 0 && B.second == 0) {
        
        return false;
    }
    
    long long judge = A.first * B.second - A.second * B.first;
    
    if (judge > 0) {
        
        return true;
    }
    else if (judge == 0) {
        
        return A.first * A.first + A.second * A.second > B.first * B.first + B.second * B.second;
    }
    else {
        
        return false;
    }
}

bool CCW3(const LLpair& A, const LLpair& B, const LLpair& C) {
    
    return CCW({B.first - A.first, B.second - A.second}, {C.first - A.first, C.second - A.second});
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    
    while (std::cin >> N) {
        
        if (!N) {
            
            break;
        }
        
        min = {10'001, 10'001};
        
        for (int idx = 0; idx < N; ++idx) {
            
            std::cin >> pts[idx].first >> pts[idx].second;
            min = std::min(min, pts[idx]);
        }
        
        for (int idx = 0; idx < N; ++idx) {
            
            pts[idx].first -= min.first;
            pts[idx].second -= min.second;
        }
        
        std::sort(pts.begin(), pts.begin() + N, CCW);
        
        std::vector<LLpair> convexHull;
        int sz;
        
        for (int idx = 0; idx < N; ++idx) {
            
            if ((sz = convexHull.size()) >= 2) {
                
                if (convexHull.back().first * pts[idx].second - convexHull.back().second * pts[idx].first == 0) {
                    
                    continue;
                }
            }
            
            while ((sz = convexHull.size()) >= 2) {
                
                if (!CCW3(convexHull[sz - 2], convexHull[sz - 1], pts[idx])) {
                    
                    convexHull.pop_back();
                }
                else {
                    
                    break;
                }
            }
            
            convexHull.push_back(pts[idx]);
        }
        
        sz = convexHull.size();
        
        long double res = 1e9, max, a, b, c, dist;
        
        for (int idx = 0; idx < sz; ++idx) {
            
            max = 0;
            
            a = convexHull[(idx + 1) % sz].second - convexHull[idx].second;
            b = - (convexHull[(idx + 1) % sz].first - convexHull[idx].first);
            c = - a * convexHull[idx].first - b * convexHull[idx].second;
            
            for (int idx2 = 0; idx2 < sz; ++idx2) {
                
                if (idx2 == idx || idx2 == (idx + 1) % sz) {
                    
                    continue;
                }
                
                dist = std::abs(a * convexHull[idx2].first + b * convexHull[idx2].second + c) / std::sqrt(a * a + b * b);
                max = std::max(max, dist);
            }
            
            res = std::min(res, max);
        }
        
        std::cout << "Case " << ++cnt << ": ";
        
        if (std::abs(res * 100 - std::round(res * 100)) < 1e-9) {
            
            std::cout << res << '\n';
        }
        else {
            
            std::cout << std::ceil(res * 100) / 100 << '\n';
        }
    }
    
    return 0;
}

