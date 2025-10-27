#include "bits/stdc++.h"


int C, N, Q, cnt1, cnt2;
const int root = 0;

struct node {
    
    std::array<int, 26> next;
    bool isEnd;
};

std::array<node, 4'000'001> color, nick;

void insert(const std::string& s, std::array<node, 4'000'001>& trie, int& cnt) {
    
    int cursor = root, sz = s.size();
    
    for (int idx = 0; idx < sz; ++idx) {
        
        if (trie[cursor].next[s[idx] - 'a']) {
            
            cursor = trie[cursor].next[s[idx] - 'a'];
        }
        else {
            
            cursor = trie[cursor].next[s[idx] - 'a'] = ++cnt;
        }
    }
    
    trie[cursor].isEnd = true;
}

void check(std::string& s) {
    
    int cursor = root, sz = s.size();
    std::vector<bool> isColorEnd(sz - 1);
    
    for (int idx = 0; idx < sz - 1; ++idx) {
        
        if (color[cursor].next[s[idx] - 'a']) {
            
            cursor = color[cursor].next[s[idx] - 'a'];
            
            if (color[cursor].isEnd) {
                
                isColorEnd[idx] = true;
            }
        }
        else {
            
            break;
        }
    }
    
    std::reverse(s.begin(), s.end());
    cursor = root;
    
    for (int idx = 0; idx < sz - 1; ++idx) {
        
        if (nick[cursor].next[s[idx] - 'a']) {
            
            cursor = nick[cursor].next[s[idx] - 'a'];
            
            if (nick[cursor].isEnd && isColorEnd[sz - 2 - idx]) {
                
                std::cout << "Yes\n";
                return;
            }
        }
        else {
            
            break;
        }
    }
    
    std::cout << "No\n";
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> C >> N;
    
    std::string s;
    
    for (int idx = 0; idx < C; ++idx) {
        
        std::cin >> s;
        insert(s, color, cnt1);
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> s;
        std::reverse(s.begin(), s.end());
        insert(s, nick, cnt2);
    }
    
    std::cin >> Q;
    
    while (Q--) {
        
        std::cin >> s;
        check(s);
    }
    
    return 0;
}