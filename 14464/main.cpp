#include "bits/stdc++.h"

constexpr int N_MAX = 20'000, C_MAX = 20'000;

int C, N;

std::vector<std::pair<int, int>> animals;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> C >> N;
    
    animals.reserve(C + N);
    
    for (int T, idx = 0; idx < C; ++idx) {
        
        std::cin >> T;
        animals.push_back({T, INT_MAX});
    }
    
    for (int A, B, idx = 0; idx < N; ++idx) {
        
        std::cin >> A >> B;
        animals.push_back({A, B});
    }
}

void solve() {
    
    std::sort(animals.begin(), animals.end());
    
    int res = 0;
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;
    
    for (const auto& [A, B] : animals) {
        
        if (B != INT_MAX) { // cow
            
            pq.push(B);
        }
        else { // chicken
            
            while (!pq.empty()) {
                
                if (pq.top() >= A) {
                    
                    ++res;
                    pq.pop();
                    break;
                }
                else {
                    
                    pq.pop();
                }
            }
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