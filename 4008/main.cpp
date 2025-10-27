/*

S[i] : sum(X[j], j: 1~i)

DP[i] = max( DP[j] + A * (S[i] - S[j]) ^ 2 + B * (S[i] - S[j]) + C )
= A*S[i]^2+B*S[i]+C + max( DP[j]+A*S[j]^2-B*S[j] + (B-2*A*S[j]) * S[i] )
= A*S[i]^2+B*S[i]+C + min( -DP[j]-A*S[j]^2+B*S[j] + (2*A*S[j]-B) * S[i] )
= CONSTANT + min( b[j] + a[j] * c[i] )

X = c[i] = S[i] : monotone increase
b[j] = 2*A*S[j]-B : monotone decrease

*/


#include "bits/stdc++.h"

constexpr int N_MAX = 1'000'001;

int N;
long long A, B, C;

std::array<long long, N_MAX> S, DP;
std::array<long double, N_MAX> starting;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> A >> B >> C;
    
    for (int idx = 1; idx <= N; ++idx) {
        
        std::cin >> S[idx];
        S[idx] += S[idx - 1];
    }
}

void solve() {
    
    std::vector<int> survivedIdx;
    survivedIdx.reserve(N);
    survivedIdx.push_back(0);
    DP[0] = 0;
    
    for (int cursor = 0, idx = 1; idx <= N; ++idx) {
        
        while (cursor < survivedIdx.size() - 1 && S[idx] >= starting[survivedIdx[cursor + 1]]) cursor++;
        
        DP[idx] = DP[survivedIdx[cursor]] + A * (S[idx] - S[survivedIdx[cursor]]) * (S[idx] - S[survivedIdx[cursor]]) + B * (S[idx] - S[survivedIdx[cursor]]) + C;
        
        long double aIdx = 2 * A * S[idx] - B;
        long double bIdx = - DP[idx] - A * S[idx] * S[idx] + B * S[idx];
        
        while (!survivedIdx.empty()) {
            
            auto back = survivedIdx.back();
            
            long double aBack = 2 * A * S[back] - B;
            long double bBack = - DP[back] - A * S[back] * S[back] + B * S[back];
            
            starting[idx] = (bIdx - bBack) / (aBack - aIdx);
            
            if (starting[idx] <= starting[back]) {
                
                survivedIdx.pop_back();
                if (cursor == survivedIdx.size()) cursor--;
            }
            else break;
        }
        
        survivedIdx.push_back(idx);
    }
    
    std::cout << DP[N];
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}



