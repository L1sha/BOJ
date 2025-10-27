#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;
const int INF = 10'001;

using Point = std::pair<int, int>;

int N;

std::array<Point, N_MAX> pts;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> pts[idx].first >> pts[idx].second;
}

int dist(Point& A, Point& B) {
    
    return (A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second);
}

int minDist(int l = 0, int r = N) {
    
    if (r - l == 2) return dist(pts[l], pts[l + 1]);
    else if (r - l == 3) return std::min(std::min(dist(pts[l], pts[l + 1]), dist(pts[l + 1], pts[l + 2])), dist(pts[l + 2], pts[l]));
    
    int mid = (l + r) / 2;
    int ans = std::min(minDist(l, mid), minDist(mid, r));
    
    int lIdx = std::distance(pts.begin(), std::lower_bound(pts.begin() + l, pts.begin() + r, std::make_pair(pts[mid].first - (int)sqrt(ans), -INF)));
    int rIdx = std::distance(pts.begin(), std::upper_bound(pts.begin() + l, pts.begin() + r, std::make_pair(pts[mid].first + (int)sqrt(ans), INF)));
    
    lIdx = std::max(l, lIdx);
    rIdx = std::min(r, rIdx);
    
    std::vector<Point> candidates(rIdx - lIdx);
    for (int idx = 0; idx < rIdx - lIdx; ++idx) candidates[idx] = {pts[idx + lIdx].second, pts[idx + lIdx].first};
    
    std::sort(candidates.begin(), candidates.end());
    
    for (int idx = 0; idx < rIdx - lIdx; ++idx) {
        
        for (int idx2 = idx + 1; idx2 < rIdx - lIdx; ++idx2) {
            
            if ((candidates[idx].first - candidates[idx2].first) * (candidates[idx].first - candidates[idx2].first) >= ans) break;
            
            ans = std::min(ans, dist(candidates[idx], candidates[idx2]));
        }
    }
    
    return ans;
}

void solve() {
    
    std::sort(pts.begin(), pts.begin() + N);
    
    std::cout << minDist();
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}