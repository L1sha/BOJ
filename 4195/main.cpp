#include "bits/stdc++.h"


int T, F, cnt;
std::array<std::string, 2> friends;
std::array<int, 200'000> parent;
std::array<int, 200'000> numFriends;

int getParent(int idx) {
    
    if (parent[idx] != idx) return parent[idx] = getParent(parent[idx]);
    return idx;
}

void Union(int idx1, int idx2) {
    
    if (getParent(idx2) == getParent(idx1)) return;
    
    numFriends[getParent(idx1)] += numFriends[getParent(idx2)];
    parent[getParent(idx2)] = getParent(idx1);
}




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> F;
        
        cnt = 0;
        for (int idx = 0; idx < 2 * F; ++idx) {
            
            parent[idx] = idx;
            numFriends[idx] = 0;
        }
        
        std::unordered_map<std::string, int> ID;
        
        while (F--) {
            
            std::cin >> friends[0] >> friends[1];
            
            for (auto& el : friends) if (!ID.count(el)) {
                
                ID[el] = cnt++;
                numFriends[ID[el]] = 1;
            }
            
            Union(ID[friends[0]], ID[friends[1]]);
            
            std::cout << numFriends[getParent(ID[friends[0]])] << '\n';
        }
    }
    
    return 0;
}

