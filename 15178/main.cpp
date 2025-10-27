#include "bits/stdc++.h"

constexpr int N_MAX = 1e9;
constexpr std::array<long long, 2> PRIME{ 97, 1031 };
std::array<std::vector<std::vector<long long>>, 2> BINOM{
    
    std::vector<std::vector<long long>>(PRIME[0], std::vector<long long>(PRIME[0])), 
    std::vector<std::vector<long long>>(PRIME[1], std::vector<long long>(PRIME[1]))
};

long long N, M;
std::array<long long, 2> RES;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
}

constexpr void fill() {
    
    for (int pIdx = 0; pIdx < 2; ++pIdx) {
        
        const auto& prime = PRIME[pIdx];
        auto& binom = BINOM[pIdx];
        
        for (int i = 0; i < prime; ++i) {
            
            binom[i][0] = 1;
            for (int j = 1; j < i; ++j) {
                
                binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % prime;
            }
            binom[i][i] = 1;
        }
    }
}

long long power(long long base, long long expo, const int& pIdx) {
    
    const auto& prime = PRIME[pIdx];
    
    long long res = 1;
    
    for (; expo; expo >>= 1, base = (base * base) % prime) {
        
        if (expo & 1) res = (res * base) % prime;
    }
    
    return res;
}

long long inverse(const long long& N, const int& pIdx) {
    
    return power(N, PRIME[pIdx] - 2, pIdx);
}

void solve() {
    
    if (N < M - 1) {
        
        std::cout << 0 << '\n';
        return;
    }
    
    if (M == 1) {
        
        std::cout << (N == 0 ? 1 : 0) << '\n';
        return;
    }
    
    // solve (N - 1, M - 2) (mod 100'007)
    
    for (int n, m, pIdx = 0; pIdx < 2; ++pIdx) {
        
        const auto& prime = PRIME[pIdx];
        const auto& binom = BINOM[pIdx];
        auto& res = RES[pIdx];
        
        res = 1;
        n = N - 1;
        m = M - 2;
        
        while (n || m) {
            
            res = (res * binom[n % prime][m % prime]) % prime;
            n /= prime;
            m /= prime;
        }
    }
    
    /*
    ans = res[0] (mod PRIME[0])
    ans = res[1] (mod PRIME[1])
    
    => ans = PRIME[1] * X + PRIME[0] * Y (mod PRIME[0] * PRIME[1])
    
    where
    PRIME[1] * X = res[0] (mod PRIME[0])
    PRIME[0] * Y = res[1] (mod PRIME[1])
    */
    
    long long ans = 0;
    
    for (int pIdx = 0; pIdx < 2; ++pIdx) {
        
        const auto& prime = PRIME[pIdx];
        const auto& anotherPrime = PRIME[(pIdx + 1) & 1];
        const auto& res = RES[pIdx];
        
        ans += anotherPrime * ((inverse(anotherPrime, pIdx) * res) % prime);
        ans %= (prime * anotherPrime);
    }
    
    std::cout << ans << '\n';
}



int main(int argc, char** argv) {
    
    fastIO();
    fill();
    int T; std::cin >> T;
    while (T--) {
        
        get_input();
        solve();
    }
    
    return 0;
}