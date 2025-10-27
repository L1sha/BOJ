#include "bits/stdc++.h"

constexpr int N_MAX = 300'000, Q_MAX = 600'000;

int N, Q;
std::vector<int> parents, cnt;
std::vector<bool> isOdd, hasOddCycle;
int res;

int getParent(int curr) {
    
    if (curr == parents[curr]) return curr;
    
    int root = getParent(parents[curr]);
    if (parents[curr] != root) {
        
        if (isOdd[parents[curr]]) isOdd[curr] = !isOdd[curr];
        parents[curr] = root;
    }
    return root;
}

void doUnion(int left, int right) {
    
    int pL = getParent(left), pR = getParent(right);
    
    if (pL == pR) {
        
        if (!hasOddCycle[pL] && isOdd[left] == isOdd[right]) {
            
            hasOddCycle[pL] = true;
            res += cnt[pL];
        }
    }
    else {
        
        parents[pR] = pL;
        
        if (hasOddCycle[pL] && !hasOddCycle[pR]) {
            
            res += cnt[pR];
        }
        else if (!hasOddCycle[pL] && hasOddCycle[pR]) {
            
            hasOddCycle[pL] = true;
            res += cnt[pL];
        }
        
        if (isOdd[left] == isOdd[right]) isOdd[pR] = true;
        
        cnt[pL] += cnt[pR];
    }
}


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> Q;
    
    parents.resize(N + 1);
    std::iota(parents.begin(), parents.end(), 0);
    cnt.resize(N + 1, 1);
    isOdd.resize(N + 1);
    hasOddCycle.resize(N + 1);
}

void solve() {
    
    for (int a, b; Q--; ) {
        
        std::cin >> a >> b;
        doUnion(a, b);
        std::cout << res << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}