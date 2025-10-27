#include "bits/stdc++.h"

constexpr int N_MAX = 4'000'000;
constexpr long long BASE = 1'299'709, PRIME = 1'000'000'007;

int N;
std::array<int, N_MAX * 2> A;
std::array<long long, N_MAX * 2 + 1> hash, powOfBase; 


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
    for (int input, idx = 0; idx < N; ++idx) {
        
        std::cin >> input;
        A[N - 1 - idx] = input;
        A[N * 2 - 1 - idx] = input;
    }
}

void makeHash() {
    
    hash[0] = 0;
    powOfBase[0] = 1;
    
    for (int idx = 0; idx < N * 2; ++idx) {
        
        hash[idx + 1] = (hash[idx] * BASE + A[idx]) % PRIME;
        powOfBase[idx + 1] = (powOfBase[idx] * BASE) % PRIME;
    }
}

long long sub(int idx1, int idx2) {
    
    long long res = (hash[idx2 + 1] - hash[idx1 + 1] * powOfBase[idx2 - idx1]) % PRIME;
    
    if (res < 0) res += PRIME;
    
    return res;
}

int myMin(int k1, int k2) {
    
    if (A[N - 1 - k1] != A[N - 1 - k2]) {
        
        if (A[N - 1 - k1] < A[N - 1 - k2]) return k1;
        else return k2;
    }
    
    if (sub(N - k1 - 2, N - k1 - 2 + N) == sub(N - k2 - 2, N - k2 - 2 + N)) {
        
        return k1;
    }
    
    int l = 0, r = N - 1, mid = (l + r) / 2;
    
    while (r - l > 1) {
        
        if (sub(N - k1 - 2, N - k1 - 1 + mid) == sub(N - k2 - 2, N - k2 - 1 + mid)) {
            
            l = mid;
        }
        else r = mid;
        
        mid = (l + r) / 2;
    }
    
    if (A[N - 1 - k1 + r] < A[N - 1 - k2 + r]) return k1;
    else return k2;
}

void solve() {
    
    makeHash();
    
    int minK = 0;
    
    for (int newK = 1; newK < N - 1; ++newK) {
        
        minK = myMin(minK, newK);
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cout << A[N - minK - 1 + idx] << ' ';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}