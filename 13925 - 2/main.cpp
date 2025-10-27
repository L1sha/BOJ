#include "bits/stdc++.h"

constexpr int N_MAX = 100'000;

const long long PRIME = 1'000'000'007;

int N;

std::array<long long, N_MAX * 4> segTree, lazy1, lazy2;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void segInit(int cursor = 1, int l = 1, int r = N) {
    
    lazy2[cursor] = 1;
    
    if (l == r) std::cin >> segTree[cursor];
    else {
        
        segInit(cursor * 2, l, l + (r - l) / 2);
        segInit(cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = (segTree[cursor * 2] + segTree[cursor * 2 + 1]) % PRIME;
    }
}

void get_input() {
    
    std::cin >> N;
    
    segInit();
}

void lazyUpdate(const int& cursor, const int& l, const int& r) {
    
    if (lazy2[cursor] != 1) {
        
        segTree[cursor] = ((segTree[cursor] * lazy2[cursor]) + lazy1[cursor] * (r - l + 1)) % PRIME;
        
        if (l != r) {
            
            lazy1[cursor * 2] = ((lazy1[cursor * 2] * lazy2[cursor]) + lazy1[cursor]) % PRIME;
            lazy2[cursor * 2] = (lazy2[cursor * 2] * lazy2[cursor]) % PRIME;
            
            lazy1[cursor * 2 + 1] = ((lazy1[cursor * 2 + 1] * lazy2[cursor]) + lazy1[cursor]) % PRIME;
            lazy2[cursor * 2 + 1] = (lazy2[cursor * 2 + 1] * lazy2[cursor]) % PRIME;
        }
        
        lazy1[cursor] = 0;
        lazy2[cursor] = 1;
    }
    else if (lazy1[cursor]) {
        
        segTree[cursor] = (segTree[cursor] + lazy1[cursor] * (r - l + 1)) % PRIME;
        
        if (l != r) {
            
            lazy1[cursor * 2] = (lazy1[cursor * 2] + lazy1[cursor]) % PRIME;
            
            lazy1[cursor * 2 + 1] = (lazy1[cursor * 2 + 1] + lazy1[cursor]) % PRIME;
        }
        
        lazy1[cursor] = 0;
    }
}

void segUpdate(const int& ql, const int& qr, long long A, long long B, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (l > qr || r < ql) return;
    else if (l >= ql && r <= qr) {
        
        segTree[cursor] = (A * segTree[cursor] + B * (r - l + 1)) % PRIME;
        
        if (l != r) {
            
            lazy1[cursor * 2] = (lazy1[cursor * 2] * A + B) % PRIME;
            lazy2[cursor * 2] = (lazy2[cursor * 2] * A) % PRIME;
            
            lazy1[cursor * 2 + 1] = (lazy1[cursor * 2 + 1] * A + B) % PRIME;
            lazy2[cursor * 2 + 1] = (lazy2[cursor * 2 + 1] * A) % PRIME;
        }
    }
    else {
        
        segUpdate(ql, qr, A, B, cursor * 2, l, l + (r - l) / 2);
        segUpdate(ql, qr, A, B, cursor * 2 + 1, l + (r - l) / 2 + 1, r);
        
        segTree[cursor] = (segTree[cursor * 2] + segTree[cursor * 2 + 1]) % PRIME;
    }
}

long long segQuery(const int& ql, const int& qr, int cursor = 1, int l = 1, int r = N) {
    
    lazyUpdate(cursor, l, r);
    
    if (l > qr || r < ql) return 0;
    else if (l >= ql && r <= qr) return segTree[cursor];
    else return (segQuery(ql, qr, cursor * 2, l, l + (r - l) / 2) + segQuery(ql, qr, cursor * 2 + 1, l + (r - l) / 2 + 1, r)) % PRIME;
}

void solve() {
    
    int M, Q, X, Y;
    long long V;
    
    std::cin >> M;
    
    while (M--) {
        
        std::cin >> Q >> X >> Y;
        if (Q != 4) std::cin >> V;
        
        switch (Q) {
            
            case 1:
            segUpdate(X, Y, 1, V);
            break;
            
            case 2:
            segUpdate(X, Y, V, 0);
            break;
            
            case 3:
            segUpdate(X, Y, 0, V);
            break;
            
            case 4:
            std::cout << segQuery(X, Y) << '\n';
            break;
            
            default:
            break;
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}