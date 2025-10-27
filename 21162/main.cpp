#include "bits/stdc++.h"

constexpr int N_MAX = 200'000;
constexpr long long BASE = 1'299'709, PRIME = 1'000'000'007;

int N, K;
std::array<int, N_MAX * 2> A;
std::array<long long, N_MAX * 2 + 1> hash, powOfBase; 


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K;
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

bool myMin(const int& k1, const int& k2) {
    
    if (A[N - 1 - k1] != A[N - 1 - k2]) {
        
        if (A[N - 1 - k1] < A[N - 1 - k2]) return true;
        else return false;
    }
    
    if (sub(N - k1 - 2, N - k1 - 2 + N) == sub(N - k2 - 2, N - k2 - 2 + N)) {
        
        return true;
    }
    
    int l = 0, r = N - 1, mid = (l + r) / 2;
    
    while (r - l > 1) {
        
        if (sub(N - k1 - 2, N - k1 - 1 + mid) == sub(N - k2 - 2, N - k2 - 1 + mid)) {
            
            l = mid;
        }
        else r = mid;
        
        mid = (l + r) / 2;
    }
    
    if (A[N - 1 - k1 + r] < A[N - 1 - k2 + r]) return true;
    else return false;
}

void solve() {
    
    makeHash();
    
    std::vector<int> toSort(N - 1);
    std::iota(toSort.begin(), toSort.end(), 0);
    
    std::sort(toSort.begin(), toSort.end(), myMin);
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cout << A[N - 1 - toSort[K - 1] + idx] << ' ';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}