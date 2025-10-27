#include "bits/stdc++.h"


int N, M;

std::map<int, int> map;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int temp;
    
    while (N--){
        
        std::cin >> temp;
        if (map.count(temp)) map[temp]++;
        else map[temp] = 1;
    }
    
    std::cin >> M;
    
    while (M--){
        
        std::cin >> temp;
        if (map.count(temp)) std::cout << map[temp] << ' ';
        else std::cout << 0 << ' ';
    }
    
    return 0;
}


