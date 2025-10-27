#include "bits/stdc++.h"

constexpr int N_MAX = 2'000'000;

const int MIN = 0, MAX = 100'000;

int N, K;

std::array<std::pair<int, int>, N_MAX * 4> lazySeg;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void segInit(int cursor = 1, int l = 0, int r = N - 1) {
    
    if (l != r) {
        
        lazySeg[cursor] = {MIN, MAX};
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
    else {
        
        lazySeg[cursor] = {0, 0};
    }
}

void get_input() {
    
    std::cin >> N >> K;
    
    segInit();
}

void lazyUpdate(const int& cursor, const int& l, const int& r) {
    
    if (lazySeg[cursor] != std::make_pair(MIN, MAX) && l != r) {
        
        const auto& [lower, upper] = lazySeg[cursor];
        
        std::array<int, 2> nexts = {cursor * 2, cursor * 2 + 1};
        
        for (const auto& next : nexts) {
            
            const auto& [nLower, nUpper] = lazySeg[next];
            
            if (lower > nUpper) {
                
                lazySeg[next] = {lower, lower};
            }
            else if (upper < nLower) {
                
                lazySeg[next] = {upper, upper};
            }
            else {
                
                lazySeg[next] = {std::max(lower, nLower), std::min(upper, nUpper)};
            }
        }
        
        lazySeg[cursor] = {MIN, MAX};
    }
}

void segUpdatePlus(const int& ql, const int& qr, const int& val, int cursor = 1, int l = 0, int r = N - 1) {
    
    lazyUpdate(cursor, l, r);
    
    if (l > qr || r < ql) return;
    else if (l >= ql && r <= qr) {
        
        if (l != r) {
            
            lazySeg[cursor].first = val;
            
            lazyUpdate(cursor, l, r);
        }
        else {
            
            if (val > lazySeg[cursor].first) {
                
                lazySeg[cursor] = {val, val};
            }
        }
    }
    else {
        
        segUpdatePlus(ql, qr, val, cursor * 2, l, l + (r - l) / 2);
        segUpdatePlus(ql, qr, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void segUpdateMinus(const int& ql, const int& qr, const int& val, int cursor = 1, int l = 0, int r = N - 1) {
    
    lazyUpdate(cursor, l, r);
    
    if (l > qr || r < ql) return;
    else if (l >= ql && r <= qr) {
        
        if (l != r) {
            
            lazySeg[cursor].second = val;
            
            lazyUpdate(cursor, l, r);
        }
        else {
            
            if (val < lazySeg[cursor].second) {
                
                lazySeg[cursor] = {val, val};
            }
        }
    }
    else {
        
        segUpdateMinus(ql, qr, val, cursor * 2, l, l + (r - l) / 2);
        segUpdateMinus(ql, qr, val, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void getOutput(int cursor = 1, int l = 0, int r = N - 1) {
    
    if (l == r) {
        
        std::cout << lazySeg[cursor].first << '\n';
    }
    else {
        
        lazyUpdate(cursor, l, r);
        
        getOutput(cursor * 2, l, l + (r - l) / 2);
        getOutput(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
    }
}

void solve() {
    
    int O, L, R, H;;
    
    while (K--) {
        
        std::cin >> O >> L >> R >> H;
        
        if (O == 1) segUpdatePlus(L, R, H);
        else segUpdateMinus(L, R, H);
    }
    
    getOutput();
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

