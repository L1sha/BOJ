#include "bits/stdc++.h"


std::string S;
int q, l, r;
char c;

std::array<std::array<int, 26>, 200'002> cnt;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> S >> q;
    
    for (int idx = 0; idx < S.size(); ++idx){
        
        for (int alphabet = 0; alphabet < 26; ++alphabet) cnt[idx + 1][alphabet] = cnt[idx][alphabet];
        cnt[idx + 1][S[idx] - 'a']++;
    }
    
    while (q--){
        
        std::cin >> c >> l >> r;
        std::cout << cnt[r + 1][c - 'a'] - cnt[l][c - 'a'] << '\n';
    }
    
    return 0;
}


