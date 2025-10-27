#include "bits/stdc++.h"

constexpr int N_MAX = 30'001;

int N;

struct Query {
    
    enum QType {
        
        BRIDGE,
        PENGUINS,
        EXCURSION
    };
    
    int type, A, BorX;
    bool print;
};

std::vector<int> numPenguins;
std::vector<Query> queries;
std::bitset<N_MAX> visited;

std::vector<std::vector<int>> adjL;
std::vector<int> nodeNum;
std::vector<std::pair<int, int>> nodeToCoord;
std::vector<std::vector<int>> coordToNode, fenwickTree;
std::vector<std::pair<int, int>> fenwickHead;

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    numPenguins.resize(N + 1);
    adjL.resize(N + 1);
    nodeToCoord.resize(N + 1);
    nodeNum.resize(N + 1);
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> numPenguins[idx];
    
    int Q, A, BorX;
    std::string s;
    
    std::cin >> Q;
    queries.reserve(Q);
    
    for (int idx = 0; idx < Q; ++idx) {
        
        std::cin >> s >> A >> BorX;
        
        if (s[0] == 'b') queries.push_back({Query::BRIDGE, A, BorX, false});
        else if (s[0] == 'e') queries.push_back({Query::EXCURSION, A, BorX, false});
        else /* if (s[0] == 'p') */ queries.push_back({Query::PENGUINS, A, BorX, false});
    }
}

void makeTree() {
    
    std::vector<int> parents(N + 1);
    std::iota(parents.begin(), parents.end(), 0);
    
    std::function<int(int)> getParent;
    getParent = [&parents, &getParent](const int& cursor) {
        
        if (parents[cursor] == cursor) return cursor;
        else return parents[cursor] = getParent(parents[cursor]);
    };
    
    auto sameParent = [&parents, &getParent](const int& cursor1, const int& cursor2) {
        
        return parents[getParent(cursor2)] == parents[getParent(cursor1)];
    };
    
    auto Union = [&parents, &sameParent](const int& cursor1, const int& cursor2) {
        
        if (!sameParent(cursor1, cursor2)) {
            
            parents[parents[cursor2]] = parents[parents[cursor1]];
            return true;
        }
        else return false;
    };
    
    for (auto& [type, A, B, print] : queries) {
        
        if (type == Query::BRIDGE) {
            
            if (Union(A, B)) {
                
                adjL[A].push_back(B);
                adjL[B].push_back(A);
                print = true;
            }
        }
        else if (type == Query::EXCURSION) {
            
            if (sameParent(A, B)) print = true;
        }
    }
}

void initDFS(const int& cursor, const int& parent) {
    
    visited[cursor] = true;
    nodeNum[cursor] = 1;
    
    int maxNodeNum = 0;
    
    for (auto& next : adjL[cursor]) {
        
        if (next != parent) {
            
            initDFS(next, cursor);
            
            if (nodeNum[next] > maxNodeNum) {
                
                maxNodeNum = nodeNum[next];
                std::swap(adjL[cursor].front(), next);
            }
        }
    }
}

void initDFS2(const int& cursor, const int& parent) {
    
    visited[cursor] = true;
    
    nodeToCoord[cursor] = {coordToNode.size() - 1, coordToNode.back().size()};
    coordToNode.back().push_back(cursor);
    
    for (const auto& next : adjL[cursor]) {
        
        if (next != parent) {
            
            if (next == adjL[cursor].front()) {
                
                initDFS2(next, cursor);
            }
            else {
                
                coordToNode.push_back({-1});
                fenwickHead.push_back(nodeToCoord[cursor]);
                
                initDFS2(next, cursor);
            }
        }
    }
}

void fenwickUpdate(const int& order, const int& cursor, const int& val) {
    
    int temp = cursor;
    
    while (temp < fenwickTree[order].size()) {
        
        fenwickTree[order][temp] += val;
        
        temp += (temp & -temp);
    }
}

void fenwickInit() {
    
    fenwickTree.resize(coordToNode.size());
    
    for (int order = 0; order < coordToNode.size(); ++order) {
        
        fenwickTree[order].resize(coordToNode[order].size());
        
        for (int cursor = 1; cursor < fenwickTree[order].size(); ++cursor) {
            
            fenwickUpdate(order, cursor, numPenguins[coordToNode[order][cursor]]);
        }
    }
}

int fenwickQuery(const int& order, const int& cursor) {
    
    int res = 0, temp = cursor;
    
    while (temp > 0) {
        
        res += fenwickTree[order][temp];
        
        temp -= (temp & -temp);
    }
    
    return res;
}

void Update(const int& A, const int& X) {
    
    const auto& [order, cursor] = nodeToCoord[A];
    
    fenwickUpdate(order, cursor, X - numPenguins[A]);
    
    numPenguins[A] = X;
}

int Query(const int& A, const int& B) {
    
    int res = 0;
    
    auto coord1 = nodeToCoord[A];
    auto coord2 = nodeToCoord[B];
    auto& [order1, cursor1] = coord1;
    auto& [order2, cursor2] = coord2;
    
    while (order1 != order2) {
        
        if (order1 < order2) std::swap(coord1, coord2);
        
        res += fenwickQuery(order1, cursor1);
        
        coord1 = fenwickHead[order1];
    }
    
    if (cursor1 < cursor2) std::swap(cursor1, cursor2);
    
    res += fenwickQuery(order1, cursor1);
    if (cursor2 != 1) res -= fenwickQuery(order1, cursor2 - 1);
    
    return res;
}

void solve() {
    
    makeTree();
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (!visited[idx]) {
            
            initDFS(idx, 0);
        }
    }
    
    visited.reset();
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (!visited[idx]) {
            
            coordToNode.push_back({-1});
            fenwickHead.push_back({-1, 0});
            
            initDFS2(idx, 0);
        }
    }
    
    fenwickInit();
    
    for (const auto& [type, A, BorX, print] : queries) {
        
        if (type == Query::BRIDGE) {
            
            if (print) std::cout << "yes\n";
            else std::cout << "no\n";
        }
        else if (type == Query::EXCURSION) {
            
            if (print) std::cout << Query(A, BorX) << '\n';
            else std::cout << "impossible\n";
        }
        else /* if (type == Query::PENGUINS) */ {
            
            Update(A, BorX);
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

