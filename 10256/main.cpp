#include "bits/stdc++.h"

constexpr int N_MAX = 1'000'000, M_MAX = 100, ROOT = 0;

int N, M, cnt;
std::string target, marker;

struct TrieNode {
    
    std::array<int, 4> children;
    int failureNode = ROOT;
    bool isEnd = false;
};

std::vector<TrieNode> Trie;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M >> target >> marker;
    
    Trie.clear();
    Trie.resize(M * (M + 1) / 2 * M + 1);
    cnt = 0;
    
    for (auto& el : target) {
        
        if (el == 'G') el = 'B';
        else if (el == 'T') el = 'C';
        else if (el == 'C') el = 'D';
    }
    
    for (auto& el : marker) {
        
        if (el == 'G') el = 'B';
        else if (el == 'T') el = 'C';
        else if (el == 'C') el = 'D';
    }
}

void trieInsert(int left, int right) {
    
    int cursor = ROOT;
    
    for (int idx = 0; idx < M; ++idx) {
        
        char c;
        if (idx >= left && idx <= right) c = marker[right - (idx - left)];
        else c = marker[idx];
        
        int& next = Trie[cursor].children[static_cast<int>(c - 'A')];
        
        if (next == ROOT) next = ++cnt;
        
        cursor = next;
    }
    
    Trie[cursor].isEnd = true;
}

void getFailureNode() {
    
    std::queue<std::tuple<int, int, int>> q;
    q.push({ROOT, -1, -1});
    Trie[ROOT].failureNode = -1;
    
    while (!q.empty()) {
        
        auto [cursor, parent, last] = q.front();
        q.pop();
        
        for (int idx = 0; idx < 4; ++idx) {
            
            const auto& next = Trie[cursor].children[idx];
            
            if (next != ROOT) {
                
                q.push({next, cursor, idx});
            }
        }
        
        if (parent != -1) parent = Trie[parent].failureNode;
        
        while (parent != -1) {
            
            if (auto cand = Trie[parent].children[last]; cand != ROOT) {
                
                Trie[cursor].failureNode = cand;
                break;
            }
            
            parent = Trie[parent].failureNode;
        }
    }
}

int AhoCorasick() {
    
    int res = 0, cursor = ROOT;
    
    for (const auto& el : target) {
        
        while (true) {
            
            if (const int& next = Trie[cursor].children[static_cast<int>(el - 'A')]; next != ROOT) {
                
                cursor = next;
                break;
            }
            
            if (const int& retry = Trie[cursor].failureNode; retry != -1) {
                
                cursor = retry;
            }
            else break;
        }
        
        if (Trie[cursor].isEnd) ++res;
    }
    
    return res;
}

void solve() {
    
    trieInsert(0, 0);
    
    for (int left = 0; left < M - 1; ++left) {
        
        for (int right = left + 1; right < M; ++right) {
            
            trieInsert(left, right);
        }
    }
    
    getFailureNode();
    
    std::cout << AhoCorasick() << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    int T; std::cin >> T;
    while (T--) {
    
        get_input();
        solve();
    }
    return 0;
}