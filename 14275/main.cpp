#include "bits/stdc++.h"


int N, K;

struct Node {
    
    std::string value;
    std::unordered_map<std::string, int> hash;
    std::vector<std::string> rawChildren;
    std::vector<Node*> children;
    
    Node() = default;
    Node(std::string s) : value(s) {}
};



void PRINT(Node* cursor, int height) {
    
    for (int idx = 0; idx < height; ++idx) {
        
        std::cout << "--";
    }
    
    std::cout << cursor->value << '\n';
    
    std::sort(cursor->rawChildren.begin(), cursor->rawChildren.end());
    
    for (auto& el : cursor->rawChildren) {
        
        PRINT(cursor->children[cursor->hash[el]], height + 1);
    }
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    std::string temp;
    
    Node* root = new Node;
    Node* cursor;
    
    while (N--) {
        
        std::cin >> K;
        cursor = root;
        
        while (K--) {
            
            std::cin >> temp;
            if (!cursor->hash.count(temp)) {
                
                cursor->hash[temp] = cursor->children.size();
                cursor->rawChildren.push_back(temp);
                cursor->children.push_back(new Node(temp));
            }
            
            cursor = cursor->children[cursor->hash[temp]];
        } 
    }
    
    std::sort(root->rawChildren.begin(), root->rawChildren.end());
    
    for (auto& el : root->rawChildren) {
        
        PRINT(root->children[root->hash[el]], 0);
    }
    
    return 0;
}

