#include "bits/stdc++.h"

constexpr int N_MAX = 20'000;

int N;

struct input {
    
    long long A, B, C;
};

std::istream& operator>> (std::istream& is, input& i) {
    
    is >> i.A >> i.C >> i.B;
    return is;
}

std::array<input, N_MAX> inputs;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) std::cin >> inputs[idx];
}

long long count(const long long& mid) {
    
    long long cnt = 0;
    
    for (int idx = 0; idx < N; ++idx) {
        
        const auto& [A, B, C] = inputs[idx];
        
        if (A <= mid && A <= C) {
            
            if (C <= mid) cnt += 1 + (C - A) / B;
            else cnt += 1 + (mid - A) / B;
        }
    }
    
    return cnt;
}

void solve() {
    
    long long l = 0, r = INT_MAX, mid;
    
    if (!(count(r) & 1)) std::cout << "NOTHING";
    else {
        
        while (r - l > 1) {
            
            mid = (r + l) / 2;
            
            if (count(mid) & 1) r = mid;
            else l = mid;
        }
        
        std::cout << r << ' ' << count(r) - count(r - 1);
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}