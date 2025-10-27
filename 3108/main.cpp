#include "bits/stdc++.h"

int N;

struct Square {
    
    int x1, x2, y1, y2;
    
    bool includeOrigin() {
        
        if (x1 == 0 || x2 == 0) {
            
            return !(y1 > 0 || y2 < 0);
        }
        else if (y1 == 0 || y2 == 0) {
            
            return !(x1 > 0 || x2 < 0);
        }
        return false;
    }
    
    bool intersect(const Square& rhs) {
        
        if (rhs.x1 > x2 || x1 > rhs.x2) return false;
        if (rhs.y1 > y2 || y1 > rhs.y2) return false;
        if (rhs.x1 > x1 && rhs.x2 < x2 && rhs.y1 > y1 && rhs.y2 < y2) return false;
        if (x1 > rhs.x1 && x2 < rhs.x2 && y1 > rhs.y1 && y2 < rhs.y2) return false;
        return true;
    }
};

std::istream& operator>>(std::istream& is, Square& s) {
    
    is >> s.x1 >> s.y1 >> s.x2 >> s.y2;
    return is;
}

std::vector<Square> squares;
std::vector<int> parents;

int getParent(const int& cursor) {
    
    if (parents[cursor] == cursor) return cursor;
    else return parents[cursor] = getParent(parents[cursor]);
}

void Union(const int& cursor1, const int& cursor2) {
    
    parents[getParent(cursor2)] = parents[getParent(cursor1)];
}



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    
    squares.resize(N + 1);
    parents.resize(N + 1);
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> squares[idx];
        parents[idx] = idx;
    }   
}

void solve() {
    
    for (int idx = 1; idx <= N; ++idx) {
        
        if (squares[idx].includeOrigin()) {
            
            Union(idx, 0);
        }
        
        for (int idx2 = 1; idx2 < idx; ++idx2) {
            
            if (squares[idx].intersect(squares[idx2])) {
                
                Union(idx, idx2);
            }
        }
    }
    
    std::vector<bool> visited(N + 1);
    int res = -1;
    
    for (int idx = 0; idx <= N; ++idx) {
        
        if (!visited[getParent(idx)]) {
            
            visited[parents[idx]] = true;
            ++res;
        }
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

