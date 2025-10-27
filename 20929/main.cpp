#include "bits/stdc++.h"

constexpr int N_MAX = 1 << 19;

int N;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N;
}

void solve(int length = N, int al = 1, int bl = 1) {
    
    int Ainput, Binput;
    
    if (length == 1) {
        
        std::cout << "? A " << al << std::endl;
        std::cin >> Ainput;
        
        std::cout << "? B " << bl << std::endl;
        std::cin >> Binput;
        
        std::cout << "! " << std::min(Ainput, Binput) << std::endl;
    }
    else {
        
        std::cout << "? A " << al + length / 2 - 1 << std::endl;
        std::cin >> Ainput;
        
        std::cout << "? B " << bl + length / 2 - 1 << std::endl;
        std::cin >> Binput; 
        
        if (Ainput < Binput) {
            
            solve(length / 2, al + length / 2, bl);
        }
        else if (Ainput > Binput) {
            
            solve(length / 2, al, bl + length / 2);
        }
        else {
            
            std::cout << "! " << Ainput << std::endl;
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}