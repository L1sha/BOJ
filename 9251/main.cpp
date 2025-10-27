#include "bits/stdc++.h"


std::string s1, s2;
std::array<std::array<int, 1001>, 1001> memo;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> s1 >> s2;
    
    for (int idx = 0; idx < s1.size(); ++idx){
        
        for (int idx2 = 0; idx2 < s2.size(); ++idx2){
            
            if (s1[idx] == s2[idx2]) memo[idx + 1][idx2 + 1] = memo[idx][idx2] + 1;
            else memo[idx + 1][idx2 + 1] = std::max(memo[idx][idx2 + 1], memo[idx + 1][idx2]);
        }
    }
    
    std::cout << memo[s1.size()][s2.size()];
    
    return 0;
}



