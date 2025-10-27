#include "bits/stdc++.h"

constexpr int N_MAX = 300'000, M_MAX = 500, LENGTH_MAX = 5'000, ROOT = 0;

int N, M, cnt;
std::string street;
std::vector<bool> lastAns;
std::array<std::string, M_MAX> tiles;

struct TrieNode {
    
    std::array<int, 26> children;
    int failureNode = ROOT, leftMost = 0, isEnd = 0;
};

std::vector<TrieNode> Trie;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void trieInsert(const std::string& s) {
    
    int cursor = ROOT;
    
    for (const auto& el : s) {
        
        int& next = Trie[cursor].children[static_cast<int>(el - 'a')];
        if (next == ROOT) next = ++cnt;
        cursor = next;
    }
    
    Trie[cursor].isEnd = s.length();
}

void get_input() {
    
    std::cin >> N >> street >> M;
    lastAns.resize(N, true);
}

void makeFailureNode() {
    
    std::queue<std::tuple<int, int, int>> q;
    q.push({ROOT, -1, -1});
    Trie[ROOT].failureNode = -1;
    
    while (!q.empty()) {
        
        auto [cursor, parent, last] = q.front();
        q.pop();
        
        for (int idx = 0; idx < 26; ++idx) {
            
            const auto& next = Trie[cursor].children[idx];
            
            if (next != ROOT) {
                
                q.push({next, cursor, idx});
            }
        }
        
        if (parent != -1) parent = Trie[parent].failureNode;
        
        while (parent != -1) {
            
            if (const auto& cand = Trie[parent].children[last]; cand != ROOT) {
                
                Trie[cursor].failureNode = cand;
                break;
            }
            
            parent = Trie[parent].failureNode;
        }
        
        for (auto temp = cursor; temp != -1; temp = Trie[temp].failureNode) {
            
            if (const auto& cand = Trie[temp].isEnd; cand != 0) {
                
                Trie[cursor].leftMost = cand;
                break;
            }
        }
    }
}

void AhoCorasick() {
    
    int res = N, cursor = 0, left = -1, right = -1;
    
    for (int idx = 0; idx < N; ++idx) {
        
        int childIdx = static_cast<int>(street[idx] - 'a');
        
        while (cursor != -1) {
            
            if (const auto& cand = Trie[cursor].children[childIdx]; cand != ROOT) {
                
                cursor = cand;
                break;
            }
            
            cursor = Trie[cursor].failureNode;
        }
        
        if (cursor == -1) cursor = ROOT;
        
        if (const auto& leftMost = Trie[cursor].leftMost; leftMost != 0) {
            
            int newRight = idx, newLeft = newRight - leftMost + 1;
            
            if (left != -1) {
                
                if (newLeft > right) {
                    
                    for (int idx = left; idx <= right; ++idx) {
                        
                        lastAns[idx] = false;
                    }
                }
                else {
                    
                    for (int idx = left; idx < newLeft; ++idx) {
                        
                        lastAns[idx] = false;
                    }
                }
            }
            
            left = newLeft;
            right = newRight;
        }
    }
    
    if (left != -1) {
        
        for (int idx = left; idx <= right; ++idx) {
            
            lastAns[idx] = false;
        }
    }
}

void solve() {
    
    while (M) {
        
        Trie.clear();
        Trie.resize(M_MAX * LENGTH_MAX);
        cnt = 0;
        
        int size = M >= 500 ? 500 : M;
        M -= size;
        
        for (std::string tile; size--; ) {
            
            std::cin >> tile;
            trieInsert(tile);
        }
        
        makeFailureNode();
        AhoCorasick();
    }
    
    int res = 0;
    
    for (const auto& el : lastAns) {
        
        if (el) ++res;
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}