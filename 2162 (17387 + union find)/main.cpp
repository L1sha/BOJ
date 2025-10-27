#include "bits/stdc++.h"

int N, res;
const long long zero = 0;

std::array<std::array<int, 4>, 3000> pts;
std::array<int, 3000> parent;
std::array<int, 3000> ptNum;

int getParent(int idx) {
    
    if (idx != parent[idx]) return parent[idx] = getParent(parent[idx]);
    return idx;
}

void Union(int idx1, int idx2) {
    
    ptNum[getParent(idx1)] += ptNum[getParent(idx2)];
    parent[getParent(idx2)] = getParent(idx1);
}

bool cross(const std::array<int, 4>& pt1, const std::array<int, 4>& pt2) {
    
    long long X1 = pt1[0];
    long long Y1 = pt1[1];
    long long X2 = pt1[2];
    long long Y2 = pt1[3];
    
    long long X3 = pt2[0];
    long long Y3 = pt2[1];
    long long X4 = pt2[2];
    long long Y4 = pt2[3];
    
    bool res = false;
    
    if (X1 > X2) { std::swap(X1, X2); std::swap(Y1, Y2); } 
    
    X2 -= X1;   // X2 >= 0
    X3 -= X1;
    X4 -= X1;
    Y2 -= Y1;
    Y3 -= Y1;
    Y4 -= Y1;
    X1 = 0;
    Y1 = 0;
    
    long long a = Y2, b = - X2; // P1, P2 : ax + by = 0
    
    long long judge3 = a * X3 + b * Y3, judge4 = a * X4 + b * Y4;
    
    if (!judge3 && !judge4) {   //  both P3 & P4 are on the line
        
        if (X2 == 0){   // line x = 0
            
            if ((Y3 >= std::min(zero, Y2) && Y3 <= std::max(zero, Y2)) || (Y4 >= std::min(zero, Y2) && Y4 <= std::max(zero, Y2))) res = true;
            
            else if ((Y3 < std::min(zero, Y2) && Y4 > std::max(zero, Y2)) || (Y3 > std::max(zero, Y2) && Y4 < std::min(zero, Y2))) res = true;
        }
        
        else {      // X2 > 0
            
            if ((X3 >= 0 && X3 <= X2) || (X4 >= 0 && X4 <= X2)) res = true;
            
            else if ((X3 < 0 && X4 > X2) || (X3 > X2 && X4 < 0)) res = true;
        }
        
    }
    
    else if (!judge3 || !judge4) {       // only one of P3 & P4 is on the line
        
        if (!judge4) { std::swap(X3, X4); std::swap(Y3, Y4); }  // P3 is on the line
        
        if (X2 == 0) {  // line x = 0
            
            if (Y3 >= std::min(zero, Y2) && Y3 <= std::max(zero, Y2)) res = true;
        }
        
        else {  // X2 > 0
            
            if (X3 >= 0 && X3 <= X2) res = true;
        }
    }
    
    else if ((judge3 > 0 && judge4 < 0) || (judge3 < 0 && judge4 > 0)) {    // P3, P4 is on different side
        
        if (X3 > X4) { std::swap(X3, X4); std::swap(Y3, Y4); }
        X4 -= X3; // X4 >= 0
        X1 -= X3;
        X2 -= X3;
        Y4 -= Y3;
        Y1 -= Y3;
        Y2 -= Y3;
        X3 = 0;
        Y3 = 0;
        
        long long c = Y4, d = -X4; // P3, P4 : cx + dy = 0
        
        long long judge1 = c * X1 + d * Y1, judge2 = c * X2 + d * Y2;
        
        if (!judge1 || !judge2) {   // at least one of P1, P2 is on the line
            
            res = true;
        }
        else if ((judge1 > 0 && judge2 < 0) || (judge1 < 0 && judge2 > 0)) {     // P1, P2 is on different side
        
            res = true;
        }
    }

    return res;
}




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> pts[idx][0] >> pts[idx][1] >> pts[idx][2] >> pts[idx][3];
        parent[idx] = idx;
        ptNum[idx] = 1;
    }
    
    res = N;
    for (int idx = 0; idx < N; ++idx) for (int idx2 = idx + 1; idx2 < N; ++idx2) if (getParent(idx) != getParent(idx2)) {
        
        if (cross(pts[idx], pts[idx2])) {
            
            Union(idx, idx2);
            res--;
        }
    }
    
    std::cout << res << '\n' << *std::max_element(ptNum.begin(), ptNum.begin() + N);
    
    return 0;
}