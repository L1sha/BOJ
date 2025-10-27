#include "bits/stdc++.h"


int N, M, I, J;
std::bitset<20'002> visited, visitedThistime, banned;
std::array<std::vector<int>, 20'002> condition;
std::array<std::vector<int>, 20'002> backCondition;
std::vector<int> banList;

int convert(int idx) {
    
    if (idx > 0) {
        
        return 10'001 + idx;
    }
    
    return -idx;
}

int convert(int idx, bool val) {
    
    if (val) {
        
        return 10'001 + idx;
    }
    
    return idx;
}

void ban(int idx, bool val) {
    
    idx = convert(idx, val);
    
    if (banned[idx]) {
        
        return;
    }
    
    banned[idx] = true;
    
    for (const int& prev : backCondition[idx]) {
        
        ban(prev % 10'001, prev / 10'001);
    }
}

void DFS(int idx, bool val) {
    
    if (visitedThistime[convert(idx, !val)]) {
        
        ban(idx, !val);
    }
    
    idx = convert(idx, val);
    
    if (visitedThistime[idx] || visited[idx]) {
        
        return;
    }
    visitedThistime[idx] = true;
    
    for (const int& next : condition[idx]) {
        
        DFS(next % 10'001, next / 10'001);
    }
    
    visited[idx] = true;
    visitedThistime[idx] = false;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    for (int idx = 0; idx < M; ++idx) {
        
        std::cin >> I >> J;
        
        if (I == J) {
                
            banList.push_back(convert(-I));
        }
        else if (I != -J) {
            
            condition[convert(-I)].push_back(convert(J));
            condition[convert(-J)].push_back(convert(I));
            
            backCondition[convert(J)].push_back(convert(-I));
            backCondition[convert(I)].push_back(convert(-J));
        }
    }
    
    for (auto& el : banList) {
        
        ban(el % 10'001, el / 10'001);
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (!visited[idx]) {
            
            DFS(idx, false);
        }
        
        if (!visited[idx + 10'001]) {
            
            DFS(idx, true);
        }
    }
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (banned[idx] && banned[idx + 10'001]) {
            
            std::cout << 0;
            
            return 0;
        }
    }
    
    std::cout << 1;
    
    return 0;
}

