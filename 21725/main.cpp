#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N, M;

std::array<int, N_MAX> parent, cnt;
std::array<long long, N_MAX> individual, together;
std::array<std::tuple<int, int, long long>, N_MAX> res;

int getParent(int curr) {
    
    if (curr == parent[curr]) return curr;
    else {
        
        auto root = getParent(parent[curr]);
        
        if (parent[curr] != root) {
            
            together[curr] += together[parent[curr]];
            parent[curr] = root;
        }
        
        return root;
    }
}

void doUnion(int left, int right) {
    
    int pL = getParent(left), pR = getParent(right);
    
    parent[pR] = pL;
    cnt[pL] += cnt[pR];
    together[pR] -= together[pL];
}

void pay(int curr, long long cost) {
    
    individual[curr] += cost;
    int p = getParent(curr);
    together[p] -= (cost / cnt[p]);
}


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
}

void solve() {
    
    std::iota(parent.begin(), parent.begin() + N + 1, 0);
    for (int idx = 1; idx <= N; ++idx) cnt[idx] = 1;
    
    int q, x, y;
    long long c;
    
    while (M--) {
        
        std::cin >> q;
        
        if (q == 1) {
            
            std::cin >> x >> y;
            
            doUnion(x, y);
        }
        else {
            
            std::cin >> x >> c;
            
            pay(x, c);
        }
    }
    
    std::priority_queue<std::pair<long long, int>,
    std::vector<std::pair<long long, int>>,
    std::less<>> plus, minus;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        int p = getParent(idx);
        individual[idx] += together[idx];
        if (p != idx) individual[idx] += together[p];
        
        if (individual[idx] > 0) {
            
            plus.push({individual[idx], idx});
        }
        else if (individual[idx] < 0) {
            
            minus.push({-individual[idx], idx});
        }
    }
    
    int cnt = 0, pIdx, mIdx;
    long long pVal = 0, mVal = 0, diff;
    
    while (!plus.empty() || !minus.empty()) {
        
        if (pVal == 0) {
            
            pVal = plus.top().first;
            pIdx = plus.top().second;
            plus.pop();
        }
        
        if (mVal == 0) {
            
            mVal = minus.top().first;
            mIdx = minus.top().second;
            minus.pop();
        }
        
        diff = std::min(pVal, mVal);
        pVal -= diff;
        mVal -= diff;
        
        res[cnt++] = {mIdx, pIdx, diff};
    }
    
    std::cout << cnt << '\n';
    
    for (int idx = 0; idx < cnt; ++idx) {
        
        const auto& [x, y, c] = res[idx];
        
        std::cout << x << ' ' << y << ' ' << c << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}