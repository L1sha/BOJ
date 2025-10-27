#include "bits/stdc++.h"


int N, M;
int X1, Y1, X2, Y2;
std::array<int, 1048577> nums; 

int squareSum(){
    
    X1--; Y1--; X2--; Y2--;
    
    int res = nums[X2 * N + Y2] - nums[X1 * N + Y1 - 1];
    int temp;
    
    if (Y2 - Y1 == N - 1) return res;
    
    for (int X = X1; X < X2; ++X){
        
        temp = nums[(X + 1) * N  + Y1 - 1] - nums[X * N + Y2];
        res -= temp;
    }
    
    return res;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> nums[0];
    
    for (int idx = 1; idx < N * N; ++idx){
        
        std::cin >> nums[idx];
        nums[idx] += nums[idx - 1];
    }
    
    while (M--) {
        
        std::cin >> X1 >> Y1 >> X2 >> Y2;
        std::cout << squareSum() << '\n';
    }
    
    return 0;
}


