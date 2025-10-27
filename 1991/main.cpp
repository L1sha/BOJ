#include "bits/stdc++.h"


int N, sz = 0;
std::map<char, int> findIdx;


struct Node {
    
    char value;
    int lIdx = -1, rIdx = -1;
    
    Node() = default;
    
    Node(char first, char second, char third) {
        
        value = first;
        if (second != '.') lIdx = findIdx[second];
        if (third != '.') rIdx = findIdx[third];
    }
};

std::array<Node, 27> nodes;

void preorder(int idx){
    
    std::cout << nodes[idx].value;
    if (nodes[idx].lIdx != -1) preorder(nodes[idx].lIdx);
    if (nodes[idx].rIdx != -1) preorder(nodes[idx].rIdx);
}

void inorder(int idx){
    
    if (nodes[idx].lIdx != -1) inorder(nodes[idx].lIdx);
    std::cout << nodes[idx].value;
    if (nodes[idx].rIdx != -1) inorder(nodes[idx].rIdx);
}

void postorder(int idx){
    
    if (nodes[idx].lIdx != -1) postorder(nodes[idx].lIdx);
    if (nodes[idx].rIdx != -1) postorder(nodes[idx].rIdx);
    std::cout << nodes[idx].value;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    char first, second, third;
    
    while (N--){
        
        std::cin >> first >> second >> third;
        
        if (!findIdx.count(first)) findIdx[first] = sz++;
        if (second != '.' && !findIdx.count(second)) findIdx[second] = sz++;
        if (third != '.' && !findIdx.count(third)) findIdx[third] = sz++;
        
        nodes[findIdx[first]] = Node(first, second, third);
    }
    
    preorder(findIdx['A']);
    std::cout << '\n';
    inorder(findIdx['A']);
    std::cout << '\n';
    postorder(findIdx['A']);
    
    return 0;
}


