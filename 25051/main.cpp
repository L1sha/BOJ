#include "bits/stdc++.h"

constexpr int N_MAX = 100'000, M_MAX = 200;
constexpr long long S_MAX = 1e12, P_MAX = 1e18;

int N, M;

using Star = std::tuple<long long, long long, long long>;

std::vector<Star> stars;
std::vector<long long> P, beautySum;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    
    stars.resize(N);
    for (auto& [X, Y, S] : stars) std::cin >> X >> Y >> S;
    
    P.resize(M);
    beautySum.resize(M);
    for (auto& el : P) std::cin >> el;
}

bool myComp(const Star& P1, const Star& P2) {
    
    const auto& [X1, Y1, S1] = P1;
    const auto& [X2, Y2, S2] = P2;
    const auto distSquare1 = X1 * X1 + Y1 * Y1;
    const auto distSquare2 = X2 * X2 + Y2 * Y2;
    
    if (X1 * Y2 - X2 * Y1 == 0) {
        
        if (X1 == 0) { // && X2 == 0
            
            if (Y1 * Y2 > 0) return distSquare1 < distSquare2;
            else return Y1 > 0;
        }
        else { // X1 != 0 && X2 != 0
            
            if (X1 * X2 > 0) return distSquare1 < distSquare2;
            else return Y1 > 0 || Y1 == 0 && X1 > 0;
        }
    }
    
    if (Y1 == 0) {
        
        if (X1 > 0) return true;
        else { // X1 < 0 
            
            if (Y2 > 0) return false;
            else /* Y2 < 0 */ return true;
        }
    }
    else if (Y1 > 0) {
        
        if (Y2 == 0) return X2 < 0;
        else if (Y2 < 0) return true;
        else /* Y2 > 0 */ return X1 * Y2 - X2 * Y1 > 0;
    }
    else /* Y1 < 0 */ {
        
        if (Y2 >= 0) return false;
        else /* Y2 < 0 */ return X1 * Y2 - X2 * Y1 > 0;
    }
}

bool sameLine(const Star& P1, const Star& P2) {
    
    const auto& [X1, Y1, S1] = P1;
    const auto& [X2, Y2, S2] = P2;
    
    if (X1 * Y2 - X2 * Y1 != 0) return false;
    else {
        
        if (X1 == 0) /* && X2 == 0 */ return Y1 * Y2 > 0;
        else /* X1 != 0 && X2 != 0 */ return X1 * X2 > 0;
    }
}

bool in90Degree(const Star& P1, const Star& P2) {
    
    const auto& [X1, Y1, S1] = P1;
    const auto& [X2, Y2, S2] = P2;
    const auto distSquare1 = X1 * X1 + Y1 * Y1;
    const auto distSquare2 = X2 * X2 + Y2 * Y2;
    
    if (X1 * Y2 - X2 * Y1 == 0) {
        
        if (X1 == 0) { // && X2 == 0
            
            if (Y1 * Y2 > 0) return distSquare1 <= distSquare2;
            else return false;
        }
        else { // X1 != 0 && X2 != 0
            
            if (X1 * X2 > 0) return distSquare1 <= distSquare2;
            else return false;
        }
    }
    
    if (X1 * Y2 - X2 * Y1 < 0) return false;
    
    const auto X3 = -Y1, Y3 = X1;
    
    return X2 * Y3 - X3 * Y2 >= 0;
}

void solve() {
    
    std::sort(stars.begin(), stars.end(), myComp);
    std::sort(P.begin(), P.end(), std::greater<>());
    for (int idx = 0; idx < M; ++idx) beautySum[idx] = -P[idx];
    
    long long res = -1e18;
    
    for (int idx = 0, idx2 = 0; idx < N; ++idx) {
        
        const auto& [X1, Y1, S1] = stars[idx];
        
        while (in90Degree(stars[idx], stars[idx2])) {
            
            const auto& [X2, Y2, S2] = stars[idx2];
            const auto distSquare2 = X2 * X2 + Y2 * Y2;
            
            for (int idx3 = 0; idx3 < M; ++idx3) {
                
                if (distSquare2 > P[idx3]) break;
                
                beautySum[idx3] += S2;
            }
            
            idx2 = (idx2 + 1) % N;
            
            if (idx2 == idx) break;
        }
        
        res = std::max(res, *std::max_element(beautySum.begin(), beautySum.end()));
        
        const auto distSquare = X1 * X1 + Y1 * Y1;
        
        for (int idx3 = 0; idx3 < M; ++idx3) {
            
            if (distSquare > P[idx3]) break;
            
            beautySum[idx3] -= S1;
        }
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}