#include "bits/stdc++.h"


int N;

std::array<std::array<int, 1001>, 1001> memo;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::string s1, s2;
    
    std::cin >> s1 >> s2;
    
    int sz1 = s1.size(), sz2 = s2.size();
    
    for (int idx = 0; idx < sz1; ++idx) for (int idx2 = 0; idx2 < sz2; ++idx2){
        
        if (s1[idx] == s2[idx2]) memo[idx + 1][idx2 + 1] = memo[idx][idx2] + 1;
        else memo[idx + 1][idx2 + 1] = std::max(memo[idx][idx2 + 1], memo[idx + 1][idx2]);
    }
    
    std::cout << memo[sz1][sz2] << '\n';
    
    int cnt = 0, cursor1 = sz1, cursor2 = sz2;
    std::string res;
    
    while (cnt != memo[sz1][sz2]){
        
        if (s1[cursor1 - 1] == s2[cursor2 - 1]){
            
            cnt++;
            res += s1[cursor1 - 1];
            cursor1--;
            cursor2--;
        }
        else if (memo[cursor1 - 1][cursor2] >= memo[cursor1][cursor2 - 1]) cursor1--;
        else cursor2--;
    }
    
    std::reverse(res.begin(),res.end());
    std::cout << res;
    
    
    return 0;
}


