#include "bits/stdc++.h"

constexpr int N_MAX = 100;
constexpr long long K_MAX = 2e12;

int N;
long long K;

std::vector<std::tuple<long long, long long, int>> CTS;
std::vector<std::pair<long long, long long>> occupied;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K;
    
    CTS.resize(N);
    for (auto& [C, T, S] : CTS) std::cin >> C >> T >> S;
    
    occupied.clear();
    occupied.push_back({0, 0});
    occupied.push_back({K + 1, K + 1});
}

long long solve() {
    
    std::sort(CTS.begin(), CTS.end(), [](const auto& lhs, const auto& rhs){
        
        const auto& [lc, lt, ls] = lhs;
        const auto& [rc, rt, rs] = rhs;
        
        return ls > rs;
    });
    
    long long res = 0;
    
    for (auto& [C, T, S] : CTS) {
        
        auto it = occupied.rbegin();
        
        std::vector<std::pair<long long, long long>> toBeInserted;
        
        for (; it + 1 != occupied.rend() && C > 0; ++it) {
            
            const auto& [l1, r1] = *(it + 1);
            const auto& [l2, r2] = *it;
            
            if (r1 < T && l2 > r1 + 1) {
                
                auto newR = std::min(l2 - 1, T);
                auto newL = std::max(r1 + 1, newR - C + 1);
                
                res += S * (newR - newL + 1);
                toBeInserted.push_back({newL, newR});
                C -= (newR - newL + 1);
            }
        }
        
        occupied.insert(occupied.end(), toBeInserted.begin(), toBeInserted.end());;
        std::sort(occupied.begin(), occupied.end());
    }
    
    return res;
}



int main(int argc, char** argv) {
    
    fastIO();
    int T; std::cin >> T;
    for (int t = 1; t <= T; ++t) {
        
        get_input();
        std::cout << "Case #" << t << ": " << solve() << '\n';
    }
    
    return 0;
}