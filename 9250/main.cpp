#include "bits/stdc++.h"

constexpr int N_MAX = 1000, S_LENGTHMAX = 100, ROOT = 0;

int N, cnt;

struct TrieNode {
    
    std::array<int, 26> children;
    int failureNode = 0;
    bool hasEnd = false;
};

std::array<TrieNode, N_MAX * S_LENGTHMAX + 1> Trie;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void trieInsert(const std::string& s) {
    
    int cursor = ROOT;
    
    for (const auto& el : s) {
        
        auto& idx = Trie[cursor].children[static_cast<int>(el - 'a')];
        
        if (idx == 0) {
            
            idx = ++cnt;
        }
        
        cursor = idx;
    }
    
    Trie[cursor].hasEnd = true;
}

void get_input() {
    
    std::cin >> N;
    
    for (std::string s; N--; ) {
        
        std::cin >> s;
        trieInsert(s);
    }
}

void getFailure() {
    
    std::queue<std::tuple<int, int, int>> q;
    
    Trie[ROOT].failureNode = -1;
    q.push({ROOT, -1, -1});
    
    while (!q.empty()) {
        
        auto [cursor, parent, lastAlphabet] = q.front();
        q.pop();
        
        for (int idx = 0; idx < 26; ++idx) {
            
            if (auto child = Trie[cursor].children[idx]; child) {
                
                q.push({child, cursor, idx});
            }
        }
        
        if (parent != -1) parent = Trie[parent].failureNode;
        
        while (parent != -1) {
            
            if (auto candidate = Trie[parent].children[lastAlphabet]; candidate) {
                
                Trie[cursor].failureNode = candidate;
                break;
            }
            
            parent = Trie[parent].failureNode;
        }
        
        for (auto temp = cursor; temp != -1; temp = Trie[temp].failureNode) {
            
            if (Trie[temp].hasEnd) {
                
                Trie[cursor].hasEnd = true;
                break;
            }
        }
    }
}

bool AhoCorasick(const std::string& s) {
    
    int cursor = ROOT;
    
    for (const auto& el : s) {
        
        auto alphabet = static_cast<int>(el - 'a');
        
        while (cursor != -1) {
            
            if (auto candidate = Trie[cursor].children[alphabet]; candidate) {
                
                cursor = candidate;
                if (Trie[cursor].hasEnd) return true;
                break;
            }
            
            cursor = Trie[cursor].failureNode;
        }
        
        if (cursor == -1) cursor = ROOT;
    }
    
    return false;
}

void solve() {
    
    getFailure();
    
    int Q;
    std::cin >> Q;
    
    for (std::string s; Q--; ) {
        
        std::cin >> s;
        
        if (AhoCorasick(s)) std::cout << "YES\n";
        else std::cout << "NO\n";
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}