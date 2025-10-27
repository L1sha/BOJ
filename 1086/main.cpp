#include "bits/stdc++.h"


int N, K;

std::array<std::string, 15> rawNums;
std::array<int, 15> nums;
std::array<int, 15> size;
std::array<int, 51> power;
std::array<std::array<std::optional<long long>, 100>, (1 << 15)> memo;
std::array<std::array<std::vector<int>, 100>, 100> nextRemain;

long long solve(int bitMask, int remain){
    
    if (!bitMask) {
        
        if (!remain) {
            
            return 1;
        }
        
        return 0;
    }
    
    if (memo[bitMask][remain].has_value()) {
        
        return memo[bitMask][remain].value();
    }
    
    int temp = bitMask, cursor = 0;
    long long res = 0;
    std::vector<int> candidates;
    
    while (temp) {
        
        if (temp % 2) candidates.push_back(cursor);
        
        cursor++;
        temp /= 2;
    }
    
    for (auto& candidate : candidates) {
        
        for (auto& next : nextRemain[power[size[candidate]]][(remain - nums[candidate] + K) % K]) {
            
            res += solve(bitMask & ~(1 << candidate), next);
        }
    }
    
    memo[bitMask][remain] = res;
    return res;
}

long long GCD(long long A, long long B){
    
    if (A == 0) {
        
        return B;
    }
    
    B %= A;
    std::swap(A, B);
    return GCD(A, B);
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> rawNums[idx];
    }
    
    std::cin >> K;
    
    power[0] = 1;
    for (int idx = 1; idx <= 50; ++idx) {
        
        power[idx] = (power[idx - 1] * 10) % K;
    }
    
    // find candidates of x satisfying mod(Ax, K) = B
    for (int A = 0; A < K; ++A) {
        
        for (int B = 0; B < K; ++B) {
            
            for (int x = 0; x < K; ++x) {
                
                if ((A * x) % K == B) {
                    
                    nextRemain[A][B].push_back(x);
                }
            }
        }
    }
    
    long long res, total = 1;
    
    for (int idx = 0; idx < N; ++idx) {
        
        total *= (idx + 1);
        
        size[idx] = rawNums[idx].size();
        
        for (int idx2 = 0; idx2 < size[idx]; ++idx2) {
            
            nums[idx] += (rawNums[idx][idx2] - '0') * power[size[idx] - 1 - idx2];
        }
        
        nums[idx] %= K;
    }
    
    res = solve((1 << N) - 1, 0);
    
    if (res == 0) {
        
        std::cout << "0/1";
    }
    else {
        
        long long g = GCD(res, total);
        
        std::cout << res / g << '/' << total / g;
    }
    
    return 0;
}

