#include "bits/stdc++.h"

constexpr int N_MAX = 1000, H_MAX = 50, M_MAX = 250;

using intPair = std::pair<int, int>;

int N, K, H, M;

std::array<intPair, N_MAX> corners;
std::array<intPair, H_MAX> holes;
std::array<intPair, M_MAX> mice;
std::array<std::vector<int>, M_MAX + H_MAX + 2> adjL;
std::array<std::array<int, M_MAX + H_MAX + 2>, M_MAX + H_MAX + 2> capa, flow;

const long long zero = 0;

std::tuple<bool, bool, long double, long double> cross(long long X1, long long Y1, long long X2, long long Y2, long long X3, long long Y3, long long X4, long long Y4) {
    
    bool res = false, onepoint = false;
    long double xOrigin = 0, yOrigin = 0, x = 0, y = 0;
    
    if (X1 > X2) { std::swap(X1, X2); std::swap(Y1, Y2); } 
    
    X2 -= X1;   // X2 >= 0
    X3 -= X1;
    X4 -= X1;
    Y2 -= Y1;
    Y3 -= Y1;
    Y4 -= Y1;
    xOrigin += X1;
    yOrigin += Y1;
    X1 = 0;
    Y1 = 0;
    
    long long a = Y2, b = - X2; // P1, P2 : ax + by = 0
    
    long long judge3 = a * X3 + b * Y3, judge4 = a * X4 + b * Y4;
    
    if (!judge3 && !judge4) {   //  both P3 & P4 are on the line
        
        if (X2 == 0){   // line x = 0
            
            if (Y2 > 0) {
                
                if (Y3 == 0) {
                    
                    res = true;
                    
                    if (Y4 < 0) {
                        
                        onepoint = true;
                        x = 0;
                        y = 0;
                    }
                }
                else if (Y3 == Y2) {
                    
                    res = true;
                    
                    if (Y4 > Y2) {
                        
                        onepoint = true;
                        x = 0;
                        y = Y2;
                    }
                }
                else if (Y3 > 0 && Y3 < Y2) {
                    
                    res = true;
                }
                else if (Y3 < 0) {
                    
                    if (Y4 >= 0) {
                        
                        res = true;
                        
                        if (Y4 == 0) {
                            
                            onepoint = true;
                            x = 0;
                            y = 0;
                        }
                    }
                }
                else {      // if (Y3 > Y2)
                    
                    if (Y4 <= Y2) {
                        
                        res = true;
                        
                        if (Y4 == Y2) {
                            
                            onepoint = true;
                            x = 0;
                            y = Y2;
                        }
                    }
                }
            }
            else {      // if (Y2 < 0)
                
                if (Y3 == 0) {
                    
                    res = true;
                    
                    if (Y4 > 0) {
                        
                        onepoint = true;
                        x = 0;
                        y = 0;
                    }
                }
                else if (Y3 == Y2) {
                    
                    res = true;
                    
                    if (Y4 < Y2) {
                        
                        onepoint = true;
                        x = 0;
                        y = Y2;
                    }
                }
                else if (Y3 < 0 && Y3 > Y2) {
                    
                    res = true;
                }
                else if (Y3 > 0) {
                    
                    if (Y4 <= 0) {
                        
                        res = true;
                        
                        if (Y4 == 0) {
                            
                            onepoint = true;
                            x = 0;
                            y = 0;
                        }
                    }
                }
                else {      // if (Y3 < Y2)
                    
                    if (Y4 >= Y2) {
                        
                        res = true;
                        
                        if (Y4 == Y2) {
                            
                            onepoint = true;
                            x = 0;
                            y = Y2;
                        }
                    }
                }
            }
        }
        else {      // if (X2 > 0)
            
            if (X3 == 0) {
                
                res = true;
                
                if (X4 < 0) {
                    
                    onepoint = true;
                    x = 0;
                    y = 0;
                }
            }
            else if (X3 == X2) {
                
                res = true;
                
                if (X4 > X2) {
                    
                    onepoint = true;
                    x = X2;
                    y = Y2;
                }
            }
            else if (X3 > 0 && X3 < X2) {
                
                res = true;
            }
            else if (X3 < 0) {
                
                if (X4 >= 0) {
                    
                    res = true;
                    
                    if (X4 == 0) {
                        
                        onepoint = true;
                        x = 0;
                        y = 0;
                    }
                }
            }
            else {  // if (X3 > X2)
                
                if (X4 <= X2) {
                    
                    res = true;
                    
                    if (X4 == X2) {
                        
                        onepoint = true;
                        x = X2;
                        y = Y2;
                    }
                }
            }
        }
    }
    else if (!judge3 || !judge4) {       // only one of P3 & P4 is on the line
        
        if (!judge4) { std::swap(X3, X4); std::swap(Y3, Y4); }  // P3 is on the line
        
        if (X2 == 0) {  // line x = 0
            
            if (Y3 >= std::min(zero, Y2) && Y3 <= std::max(zero, Y2)) {
                
                res = true;
                onepoint = true;
                x = X1;
                y = Y1 + Y3;
            }
        }
        else {  // if (X2 > 0)
            
            if (X3 >= 0 && X3 <= X2) {
                
                res = true;
                onepoint = true;
                x = X1 + X3;
                y = Y1 + Y3;
            }
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
        xOrigin += X3;
        yOrigin += Y3;
        X3 = 0;
        Y3 = 0;
        
        long long c = Y4, d = -X4; // P3, P4 : cx + dy = 0
        
        long long judge1 = c * X1 + d * Y1, judge2 = c * X2 + d * Y2;
        
        // NOTE: judge1 & judge2 cannot be zero at the same time (because judge3 != 0 & judge4 != 0)
        if (!judge1 || !judge2) {   // one of P1, P2 is on the line
            
            res = true;
            onepoint = true;
            
            if (!judge2) { std::swap(X1, X2); std::swap(Y1, Y2); }  // P1 is on the line
            
            x = X1;
            y = Y1;
        }
        else if ((judge1 > 0 && judge2 < 0) || (judge1 < 0 && judge2 > 0)) {     // P1, P2 is on different side
            
            res = true;
            onepoint = true;
            
            if (X4 == 0) {      // P3, P4 : line x = 0
                
                x = 0;
                y = Y1 + (Y2 - Y1) * (-X1) / ((long double)(X2 - X1));
            }
            else if (X1 == X2) {    // P1, P2 : line x = X1
                
                x = X1;
                y = Y4 * X1 / ((long double)X4);
            }
            else {
                
                long double a = (Y2 - Y1) / ((long double)(X2 - X1));
                long double b = Y1 - a * X1;     // P1, P2 : line y = ax + b
                long double c = Y4 / ((long double)X4); // P3, P4 : line y = cx
                
                x = b / (c - a);
                y = c * x;
            }
        }
    }
    
    x += xOrigin;
    y += yOrigin;

    return {res, onepoint, x, y};
}

bool ableToHide(const intPair& mouse, const intPair& hole) {
    
    for (int idx = 0; idx < N; ++idx) {
        
        auto [res, onepoint, x, y] = cross(mouse.first, mouse.second, hole.first, hole.second, corners[idx].first, corners[idx].second, corners[(idx + 1) % N].first, corners[(idx + 1) % N].second);
        
        if (res && (!onepoint || hole.first != x || hole.second != y)) return false;
    }
    
    return true;
}

void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K >> H >> M;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> corners[idx].first >> corners[idx].second;
    
    for (int idx = 0; idx < H; ++idx) std::cin >> holes[idx].first >> holes[idx].second;
    
    for (int idx = 0; idx < M; ++idx) std::cin >> mice[idx].first >> mice[idx].second;
}

void solve() {
    
    int source = M + H, sink = M + H + 1;
    
    for (int idx = 0; idx < M; ++idx) {
        
        adjL[source].push_back(idx);
        capa[source][idx] = 1;
        adjL[idx].push_back(source);
    }
    
    for (int idx = 0; idx < H; ++idx) {
        
        adjL[M + idx].push_back(sink);
        capa[M + idx][sink] = K;
        adjL[sink].push_back(M + idx);
    }
    
    for (int mouse = 0; mouse < M; ++mouse) {
        
        for (int hole = 0; hole < H; ++hole) {
            
            if (ableToHide(mice[mouse], holes[hole])) {
                
                adjL[mouse].push_back(M + hole);
                capa[mouse][M + hole] = 1;
                adjL[M + hole].push_back(mouse);
            }
        }
    }
    
    std::vector<int> prev(M + H + 2);
    int res = 0;
    
    while (true) {
        
        std::fill(prev.begin(), prev.end(), -1);
        
        std::queue<int> q;
        q.push(source);
        prev[source] = source;
        
        for (int cursor; !q.empty(); ) {
            
            cursor = q.front();
            q.pop();
            
            if (cursor == sink) break;
            
            for (const int& next : adjL[cursor]) {
                
                if (prev[next] == -1 && flow[cursor][next] < capa[cursor][next]) {
                    
                    prev[next] = cursor;
                    q.push(next);
                }
            }
        }
        
        if (prev[sink] == -1) break;
        
        for (int cursor = sink; cursor != source; cursor = prev[cursor]) {
            
            flow[prev[cursor]][cursor]++;
            flow[cursor][prev[cursor]]--;
        }
        
        res++;
    }
    
    if (res == M) std::cout << "Possible";
    else std::cout << "Impossible";
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

