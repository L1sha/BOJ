#include "bits/stdc++.h"


int N;

std::array<bool, 21> all;
std::array<bool, 21> empty;
std::array<bool, 21> set = {false, };




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int temp;
    std::string s;
    
    std::fill(all.begin(), all.end(), true);
    std::fill(empty.begin(), empty.end(), false);
    
    while (N--){
        
        std::cin >> s;
        if (s == "all") set = all;
        else if (s == "empty") set = empty;
        else {
            
            std::cin >> temp;
            
            if (s == "add") set[temp] = true;
            else if (s == "remove") set[temp] = false;
            else if (s == "check") { if (set[temp]) std::cout << "1\n"; else std::cout << "0\n"; }
            else if (s == "toggle") set[temp] = !set[temp];
        }
    }
    
    return 0;
}


