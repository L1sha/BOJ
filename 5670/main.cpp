#include "bits/stdc++.h"


struct node {
    
    int childrenNum;
    std::array<int, 26> next;
};

int N, cnt;
const int root = 0;
std::array<std::string, 100'000> vocab;
std::array<node, 1'000'000> nodes;

void nodeInsert(const std::string& s) {
    
    int sz = s.size(), cursor = root;
    
    for (int idx = 0; idx < sz; ++idx) {
        
        if (nodes[cursor].next[s[idx] - 'a'] == 0) {
            
            nodes[cursor].childrenNum++;
            nodes[cursor].next[s[idx] - 'a'] = cnt;
            cursor = cnt++;
        }
        else {
            
            cursor = nodes[cursor].next[s[idx] - 'a'];
        }
    }
    
    nodes[cursor].childrenNum++;
}

int nodeCheck(const std::string& s) {
    
    int sz = s.size(), res = 1, cursor = nodes[root].next[s[0] - 'a'];
    
    for (int idx = 1; idx < sz; ++idx) {
        
        if (nodes[cursor].childrenNum != 1) {
            
            res++;
        }
        
        cursor = nodes[cursor].next[s[idx] - 'a'];
    }
    
    return res;
}


int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    
    while (std::cin >> N) {
        
        for (int idx = 0; idx < cnt; ++idx) {
            
            nodes[idx].childrenNum = 0;
            std::fill(nodes[idx].next.begin(), nodes[idx].next.end(), 0);
        }
        
        cnt = 1;
        
        for (int idx = 0; idx < N; ++idx) {
            
            std::cin >> vocab[idx];
            nodeInsert(vocab[idx]);
        }
        
        int sum = 0;
        
        for (int idx = 0; idx < N; ++idx) {
            
            sum += nodeCheck(vocab[idx]);
        }
        
        std::cout << sum / (double) N << '\n';
    }
    
    return 0;
}

