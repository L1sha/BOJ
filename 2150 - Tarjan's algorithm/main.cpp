#include "bits/stdc++.h"


// Tarjan's algorithm

int N, E;

std::array<std::vector<int>, 10'001> adjL;
std::stack<int> s;
std::array<int, 10'001> visited;
std::bitset<10'001> done;
std::vector<std::vector<int>> SCCset;
int cnt;

int Tarjan(int idx) {
    
    int lowestDest = visited[idx] = ++cnt;
    s.push(idx);
    
    for (const int& next : adjL[idx]) {
        
        if (visited[next]) {
            
            if (!done[next]) {
                
                lowestDest = std::min(lowestDest, visited[next]);
            }
        }
        else {
            
            lowestDest = std::min(lowestDest, Tarjan(next));
        }
    }
    
    if (lowestDest == visited[idx]) {
        
        std::vector<int> newSCC;
        int temp;
        
        while (idx != (temp = s.top())) {
            
            newSCC.push_back(temp);
            done[temp] = true;
            s.pop();
        }
        
        newSCC.push_back(temp);
        done[temp] = true;
        s.pop();
        
        std::sort(newSCC.begin(), newSCC.end());
        SCCset.push_back(std::move(newSCC));
    }
    
    
    return lowestDest;
}

bool compareIntVector(const std::vector<int>& A, const std::vector<int>& B) {
    
    return A.front() < B.front();
}

void getSCC() {
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (!visited[idx]) {
            
            Tarjan(idx);
        }
    }
    
    std::sort(SCCset.begin(), SCCset.end(), compareIntVector);
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> E;

    int from, to;
    
    while (E--) {
        
        std::cin >> from >> to;
        adjL[from].push_back(to);
    }
    
    getSCC();
    
    std::cout << SCCset.size() << '\n';
    
    for (const auto& SCC : SCCset) {
        
        for (const auto& el : SCC) {
            
            std::cout << el << ' ';
        }
        
        std::cout << -1 << '\n';
    }
    
    return 0;
}

