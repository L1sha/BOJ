#include "bits/stdc++.h"


int N, C;

std::array<int, 200'002> X;

bool check(int minDist){
    
    int res = 1, temp = 0, cursor = 1;
    while (cursor != N){
        
        temp += (X[cursor] - X[cursor - 1]);
        if (temp >= minDist) { res++; temp = 0; }
        cursor++;
    }
    
    return res >= C;
}

int solve(){
    
    int left = 1, right = 1'000'000'001, mid;
    
    while (right - left > 1){
        
        mid = (left + right) / 2;
        
        if (check(mid)) left = mid;
        else right = mid;
    }
    
    return left;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> C;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> X[idx];
    std::sort(X.begin(), X.begin() + N);
    
    std::cout << solve();
    
    return 0;
}


