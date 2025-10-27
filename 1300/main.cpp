#include "bits/stdc++.h"


long long N, k;

bool check(long long mid){
    
    long long sum = (mid / 100'000) * N;
    for (int idx = (mid / 100'000) + 1; idx <= N; ++idx) sum += (long long) (N * ((double) mid / 100'000.0) / idx);
    
    return sum < k;
}

long long solve(){
    
    if (k == N * N) return k;
    
    long long left = 0, right = N * 100'000, mid;
    
    while (right - left > 1) {
        
        mid = (left + right) / 2;
        if (check(mid)) left = mid;
        else right = mid;
    }
    
    return (long long) (((double) right / 100'000.0) * N);
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> k;
    
    std::cout << solve();
    
    return 0;
}


