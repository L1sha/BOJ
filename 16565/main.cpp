#include "bits/stdc++.h"


// while computing combination, if you % it, * (N - k) / k  <- may be not dividible by k

int N;

const int PRIME = 10007;

std::array<std::vector<long long>, 14> comb;
std::array<int, 14> comb13;


int solve (int num) {
    
    int maxSet = num / 4, res = 0;
    
    for (int set = 1; set <= maxSet; ++set) {
        
        res = (res + PRIME + ((set % 2) * 2 - 1) * ((comb13[set] * comb[set][num - set * 4]) % PRIME)) % PRIME;
    }
    
    return res;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    for (int idx = 0; idx <= 13; ++idx) {
        
        int num = 52 - idx * 4;
        comb[idx].resize(num + 1);
        
        comb[idx][0] = 1;
        comb[idx][num] = 1;
        for (int idx2 = 1; idx2 <= num / 2; ++idx2) {
            
            comb[idx][idx2] = comb[idx][idx2 - 1] * (num + 1 - idx2) / idx2;
            comb[idx][num - idx2] = comb[idx][idx2];
        }
    }
    
    comb13[0] = 1;
    comb13[13] = 1;
    for (int idx = 1; idx <= 6; ++idx) {
        
        comb13[idx] = (comb13[idx - 1] * (14 - idx) / idx) % PRIME;
        comb13[13 - idx] = comb13[idx];
    }
    
    std::cin >> N;
    
    std::cout << solve(N);
    
    return 0;
}

