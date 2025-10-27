#include "bits/stdc++.h"

constexpr int N_MAX = 100'000, MAXHEIGHT = 30, ROOT = 0;

int N, cnt;

std::array<int, N_MAX> A;

struct TrieNode {
    
    std::array<int, 2> child{0, 0};
};

std::array<TrieNode, MAXHEIGHT * N_MAX> Trie;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void TrieInsert(int& input) {
    
    int cursor = ROOT;
    
    for (int divider = (1 << (MAXHEIGHT - 1)), quotient; divider > 0; divider >>= 1) {
        
        quotient = input / divider;
        
        if (Trie[cursor].child[quotient]) cursor = Trie[cursor].child[quotient];
        else {
            
            Trie[cursor].child[quotient] = ++cnt;
            cursor = cnt;
        }
        
        input %= divider;
    }
}

void get_input() {
    
    std::cin >> N;
    
    for (int input; N--; ) {
        
        std::cin >> input;
        
        TrieInsert(input);
    }
}

void DFS(int& res, int cur, int left, int right, int divider) {
    
    if (divider == 0) {
        
        res = std::max(res, cur);
        return;
    }
    
    if (Trie[left].child[0] && Trie[left].child[1]) {
        
        cur += divider;
        
        if (Trie[right].child[0]) {
            
            DFS(res, cur, Trie[left].child[1], Trie[right].child[0], divider >> 1);
        }
        if (Trie[right].child[1]) {
            
            DFS(res, cur, Trie[left].child[0], Trie[right].child[1], divider >> 1);
        }
    }
    else if (Trie[left].child[0]) {
        
        if (Trie[right].child[1]) {
            
            cur += divider;
            
            DFS(res, cur, Trie[left].child[0], Trie[right].child[1], divider >> 1);
        }
        else {  // if (Trie[right].child[0])
            
            DFS(res, cur, Trie[left].child[0], Trie[right].child[0], divider >> 1);
        }
    }
    else {  // if (Trie[left].child[1])
        
        if (Trie[right].child[0]) {
            
            cur += divider;
            
            DFS(res, cur, Trie[left].child[1], Trie[right].child[0], divider >> 1);
        }
        else {  // if (Trie[right].child[1])
            
            DFS(res, cur, Trie[left].child[1], Trie[right].child[1], divider >> 1);
        }
    }
}

void solve() {
    
    int res = 0, cursor = ROOT, divider = (1 << (MAXHEIGHT - 1));
    
    while (divider > 0) {
        
        if (Trie[cursor].child[0] && Trie[cursor].child[1]) {
            
            DFS(res, divider, Trie[cursor].child[0], Trie[cursor].child[1], divider >> 1);
            
            break;
        }
        
        if (Trie[cursor].child[0]) {
            
            cursor = Trie[cursor].child[0];
        }
        else { // if (Trie[cursor].child[1])
            
            cursor = Trie[cursor].child[1];
        }
        
        divider >>= 1;
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}