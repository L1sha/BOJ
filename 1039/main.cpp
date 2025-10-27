#include "bits/stdc++.h"

constexpr int N_MAX = 1'000'000, K_MAX = 11;

int N, K, digit = 0;

std::array<std::array<bool, K_MAX>, N_MAX> dp;
std::array<int, 7> POW10{1, 10, 100, 1000, 10000, 100'000, 1'000'000};


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K;
}

void fill(const int& num, const int& k) {
    
    std::vector<int> nums(digit);
    
    for (int idx = 0, temp = num; temp; temp /= 10) {
        
        nums[idx++] = temp % 10;
    }
    
    for (int idx = 0; idx < digit - 1; ++idx) {
        
        for (int idx2 = idx + 1; idx2 < digit; ++idx2) {
            
            if (idx2 == digit - 1 && nums[idx] == 0) continue;
            
            int temp = num;
            temp -= nums[idx] * POW10[idx];
            temp -= nums[idx2] * POW10[idx2];
            temp += nums[idx] * POW10[idx2];
            temp += nums[idx2] * POW10[idx];
            
            dp[temp][k + 1] = true;
        }
    }
}

void solve() {
    
    if (N == 1'000'000) {
        
        std::cout << N;
        return;
    }
    
    dp[N][0] = true;
    for (int temp = N; temp; temp /= 10) ++digit;
    
    for (int k = 0; k < K; ++k) {
        
        for (int num = POW10[digit - 1]; num < POW10[digit]; ++num) {
            
            if (dp[num][k]) {
                
                fill(num, k);
            }
        }
    }
    
    for (int num = POW10[digit] - 1; num >= POW10[digit - 1]; --num) {
        
        if (dp[num][K]) {
            
            std::cout << num;
            return;
        }
    }
    
    std::cout << -1;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}