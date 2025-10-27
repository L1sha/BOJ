#include "bits/stdc++.h"


int N, cnt;
std::array<int, 100'001> inorder;
std::array<int, 100'001> postorder;

struct Node {
    
    int val, left = -1, right = -1;
    
    Node() = default;
    Node(int v, int l) : val(v), left(l) {}
};

std::array<Node, 100'001> nodes;


int solve(int inBegin, int inEnd, int postBegin, int postEnd) {
    
    int left = -1, dist;
    
    while (inBegin < inEnd) {
        
        nodes[cnt] = Node(inorder[inBegin], left);
        left = cnt++;
        
        dist = std::distance(postorder.begin() + postBegin, std::find(postorder.begin() + postBegin, postorder.begin() + postEnd, inorder[inBegin]));
        
        nodes[left].right = solve(inBegin + 1, inBegin + 1 + dist, postBegin, postBegin + dist);
        
        inBegin = inBegin + 1 + dist;
        postBegin = postBegin + 1 + dist;
    }
    
    return left;
}

void preorder(int root) {
    
    if (root == -1) return;
    std::cout << nodes[root].val << ' ';
    preorder(nodes[root].left);
    preorder(nodes[root].right);
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> inorder[idx];
    for (int idx = 0; idx < N; ++idx) std::cin >> postorder[idx];
    
    preorder(solve(0, N, 0, N));
    
    return 0;
}


