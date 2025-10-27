#include "bits/stdc++.h"


int N;
std::array<std::array<std::array<int, 1 << 10>, 10>, 101> memo;
// [N][0~9][0000000000(2)~1111111111(2)]



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int num = 0; num <= 9; ++num) memo[1][num][1 << num] = 1;
    
    for (int idx = 2; idx <= N; ++idx){
        
        for (int num = 0; num <= 9; ++num){
            
            for (int bitMask = 0; bitMask < (1 << 10); ++bitMask){
                
                if (num != 0) {
                    
                    memo[idx][num][bitMask | (1 << num)] += memo[idx - 1][num - 1][bitMask];
                    memo[idx][num][bitMask | (1 << num)] %= 1'000'000'000;
                }
                
                if (num != 9) {
                    
                    memo[idx][num][bitMask | (1 << num)] += memo[idx - 1][num + 1][bitMask];
                    memo[idx][num][bitMask | (1 << num)] %= 1'000'000'000;
                }
            }
        }
    }
    
    int res = 0;
    for (int idx = 1; idx <= 9; ++idx) res = (res + memo[N][idx][(1 << 10) - 1]) % 1'000'000'000;
    
    std::cout << res;
    
    return 0;
}


