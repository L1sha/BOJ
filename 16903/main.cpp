#include "bits/stdc++.h"


struct Trie {
    
    std::array<int, 2> child = {0, 0};
    std::array<int, 2> cnt = {0, 0};
};

constexpr int M_MAX = 200'000;

int M, cnt;

std::array<Trie, 30 * M_MAX> trie;
std::array<int, 30> pow2;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void trieInsert(int x) {
    
    for (int cursor = 0, next, idx = 29; idx >= 0; --idx) {
        
        next = x / pow2[idx];
        x %= pow2[idx];
        
        trie[cursor].cnt[next]++;
        if (idx > 0 && trie[cursor].child[next] == 0) {
            
            trie[cursor].child[next] = ++cnt;
        }
        cursor = trie[cursor].child[next];
    }
}

void trieRemove(int x) {
    
    for (int cursor = 0, next, idx = 29; idx >= 0; --idx) {
        
        next = x / pow2[idx];
        x %= pow2[idx];
        
        trie[cursor].cnt[next]--;
        cursor = trie[cursor].child[next];
    }
}

int trieQuery(int x) {
    
    int res = 0;
    
    for (int cursor = 0, next, idx = 29; idx >= 0; --idx) {
        
        next = x / pow2[idx];
        x %= pow2[idx];
        
        if (trie[cursor].cnt[(next + 1) % 2] > 0) {
            
            res += pow2[idx];
            cursor = trie[cursor].child[(next + 1) % 2];
        }
        else {
            
            cursor = trie[cursor].child[next];
        }
    }
    
    return res;
}

void solve() {
    
    pow2[0] = 1;
    for (int idx = 1; idx < 30; ++idx) {
        
        pow2[idx] = pow2[idx - 1] * 2;
    }
    trieInsert(0);
    
    std::cin >> M;
    
    for (int query, x; M--; ) {
        
        std::cin >> query >> x;
        
        switch (query) {
            
            case 1:
            
            trieInsert(x);
            break;
            
            case 2:
            
            trieRemove(x);
            break;
            
            case 3:
            
            std::cout << trieQuery(x) << '\n';
            break;
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    solve();
    
    return 0;
}

