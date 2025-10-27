#include "bits/stdc++.h"


struct trieNode {
    
    std::array<int, 26> next;
    bool isEnd;
};

std::array<trieNode, 5'000'001> trie;

int N, M, cnt, res;
const int root = 0;
std::string input;

void insert(const std::string& s) {
    
    int cursor = root, sz = s.size();
    
    for (int idx = 0; idx < sz; ++idx) {
        
        if (trie[cursor].next[s[idx] - 'a']) {
            
            cursor = trie[cursor].next[s[idx] - 'a'];
        }
        else { 
            
            trie[cursor].next[s[idx] - 'a'] = ++cnt;
            cursor = cnt;
        }
    }
    
    trie[cursor].isEnd = true;
}

int check(const std::string& s) {
    
    int cursor = root, sz = s.size();
    
    for (int idx = 0; idx < sz; ++idx) {
        
        if (trie[cursor].next[s[idx] - 'a']) {
            
            cursor = trie[cursor].next[s[idx] - 'a'];
        }
        else { 
            
            return 0;
        }
    }
    
    if (trie[cursor].isEnd) {
        
        return 1;
    }
    else {
        
        return 0;
    }
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    while (N--) {
        
        std::cin >> input;
        insert(input);
    }
    
    while (M--) {
        
        std::cin >> input;
        res += check(input);
    }
    
    std::cout << res;
    
    return 0;
}

