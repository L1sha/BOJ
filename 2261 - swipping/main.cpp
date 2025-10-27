#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;
const int INF = 10'001;

using Point = std::pair<int, int>;

int N;
std::array<Point, N_MAX> pts;
std::set<Point> set;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> pts[idx].first >> pts[idx].second;
}

int dist(const Point& A, const Point& B) {
    
    return (A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second);
}

Point reverse(Point& A) {
    
    return {A.second, A.first};
}

void solve() {
    
    std::sort(pts.begin(), pts.begin() + N);
    
    set.insert(reverse(pts[0]));
    set.insert(reverse(pts[1]));
    
    int ans = dist(pts[0], pts[1]), cursor = 0;
    
    for (int idx = 2; idx < N; ++idx) {
        
        while (cursor < idx && (pts[cursor].first - pts[idx].first) * (pts[cursor].first - pts[idx].first) >= ans) {
            
            set.erase(reverse(pts[cursor++]));
        }
        
        auto left = set.lower_bound(std::make_pair(pts[idx].second - (int)sqrt(ans), -INF));
        auto right = set.upper_bound(std::make_pair(pts[idx].second + (int)sqrt(ans), INF));
        
        for (auto it = left; it != right; ++it) {
            
            ans = std::min(ans, dist(reverse(pts[idx]), *it));
        }
        
        set.insert(reverse(pts[idx]));
    }
    
    std::cout << ans;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

