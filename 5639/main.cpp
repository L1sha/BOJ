#include "bits/stdc++.h"


struct Node {
    
    Node *left = nullptr, *right = nullptr, *parent = nullptr;
    int value;
};

std::array<Node*, 10'001> nodes;


void postOrder(Node* nodePtr){
    
    if (nodePtr->left != nullptr) postOrder(nodePtr->left);
    if (nodePtr->right != nullptr) postOrder(nodePtr->right);
    std::cout << nodePtr->value << '\n';
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int temp, cnt = 0;
    Node *previous, *current, *root;
    
    while (std::cin >> temp){
        
        current = nodes[cnt++];
        current = new Node;
        current->value = temp;
        
        if (cnt == 1) {
            
            root = current;
            // std::cout << temp << '\n';
        }
        else if (temp < previous->value) {
            
            previous->left = current;
            current->parent = previous;
            // std::cout << temp << ' ' << previous->value << '\n';
        }
        else {
            
            Node* maxNode = previous;
            
            while (previous != root && temp > previous->parent->value) {
                
                previous = previous->parent;
                if (maxNode->value < previous->value) maxNode = previous;
            }
            
            maxNode->right = current;
            current->parent = maxNode;
            // std::cout << temp << ' ' << maxNode->value << '\n';
        }
        
        previous = current;
        
        if (std::cin.eof()) break;
    }
    
    postOrder(root);
    
    return 0;
}


