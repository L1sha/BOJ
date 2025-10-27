#include "bits/stdc++.h"


int N, cursor = 0;

std::array<int, 12> nums;
std::array<int, 4> numOperator;
std::vector<int> res;

void solve(int temp){
    
    if (cursor == N - 1) res.push_back(temp);
    else {
        
        int save = temp;
        
        for (int op = 0; op < 4; ++op) if (numOperator[op]){
            
            switch (op){
                
                case 0:
                temp += nums[cursor + 1];
                break;
                
                case 1:
                temp -= nums[cursor + 1];
                break;
                
                case 2:
                temp *= nums[cursor + 1];
                break;
                
                case 3:
                temp /= nums[cursor + 1];
                break;
            }
            
            cursor++;
            numOperator[op]--;
            solve(temp);
            numOperator[op]++;
            cursor--;
            temp = save;
        }
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) std::cin >> nums[idx];
    for (auto& el : numOperator) std::cin >> el;
    
    solve(nums[0]);
    
    std::cout << *std::max_element(res.begin(), res.end()) << '\n' << *std::min_element(res.begin(), res.end());
    
    return 0;
}


