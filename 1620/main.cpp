#include "bits/stdc++.h"


int N, M;

std::map<std::string, int> stoi;
std::map<int, std::string> itos;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    std::string s;
    
    for (int idx = 1; idx <= N; ++idx) { std::cin >> s; stoi[s] = idx; itos[idx] = s; }
    
    while (M--) {
        
        std::cin >> s;
        if (s[0] >= '0' && s[0] <= '9') std::cout << itos[std::stoi(s)] << '\n';
        else std::cout << stoi[s] << '\n';
    }
    
    return 0;
}


