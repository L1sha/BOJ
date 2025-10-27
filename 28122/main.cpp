#include "bits/stdc++.h"

constexpr int N_MAX = 200'000, H_MAX = 60, ROOT = 0;

int N, totalCnt = 0;

struct TrieNode {
    
    int cnt = 0;
    std::array<int, 2> childIdx{0, 0};
};

std::array<TrieNode, N_MAX * H_MAX> Trie;

void trieInsert(long long num) {
    
    int cursor = ROOT;
    
    ++Trie[cursor].cnt;
    
    for (int height = 0; height < H_MAX; ++height) {
        
        if (Trie[cursor].childIdx[num & 1] == ROOT) {
            
            Trie[cursor].childIdx[num & 1] = ++totalCnt;
            cursor = totalCnt;
        }
        else cursor = Trie[cursor].childIdx[num & 1];
        
        ++Trie[cursor].cnt;
        
        num >>= 1;
    }
}

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    for (long long input; N--; ) {
        
        std::cin >> input;
        trieInsert(input);
    }
}

void DFS(int& res, int cursor = ROOT, int height = 0, int cnt = 0, int cntOwn = 0) {
    
    if (cntOwn == Trie[cursor].cnt) {
        
        res = std::max(res, cnt);
        return;
    }
    
    if (height == H_MAX) {
        
        res = std::max(res, cnt + Trie[cursor].cnt - cntOwn);
        return;
    }
    
    for (int newCntOwn, opposite, idx = 0; idx < 2; ++idx) {
        
        opposite = (idx + 1) % 2;
        
        if (Trie[cursor].childIdx[idx] != ROOT) {
            
            if (Trie[cursor].childIdx[opposite] != ROOT) {
                
                newCntOwn = std::max(0, cntOwn - Trie[Trie[cursor].childIdx[opposite]].cnt);
            }
            else newCntOwn = cntOwn;
            
            DFS(res, Trie[cursor].childIdx[idx], height + 1, cnt + 1, newCntOwn + 1);
        }
    }
}

void solve() {
    
    int res = 0;
    
    DFS(res);
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}