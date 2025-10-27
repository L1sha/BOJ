#include "bits/stdc++.h"


int N;



void solve(int N) {
    
    int temp = N, power = 1, cursor, front;
    std::array<int, 10> res = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    while (temp) {
        
        cursor = temp % 10;
        temp /= 10;
        
        if (front = N / (power * 10)) {
            
            for (auto& el : res) {
                
                el += front * power;
            }
            res[0] -= power;
            
            for (int idx = 0; idx < cursor; ++idx) {
                
                res[idx] += power;
            }
            res[cursor] += (N % power + 1);
        }
        else {
            
            for (int idx = 1; idx < cursor; ++idx) {
                
                res[idx] += power;
            }
            res[cursor] += (N % power + 1);
        }
        
        power *= 10;
    }
    
    for (auto& el : res) std::cout << el << ' ';
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    solve(N);
    
    return 0;
}

