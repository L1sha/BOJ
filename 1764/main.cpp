#include "bits/stdc++.h"


int N, M;
std::unordered_set<std::string> set;
std::vector<std::string> res;



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    std::string temp;
    
    while (N--) { std::cin >> temp; set.insert(temp); }
    
    while (M--) { std::cin >> temp; if (set.find(temp) != set.end()) res.push_back(temp); }
    
    std::sort(res.begin(), res.end());
    
    std::cout << res.size() << '\n';
    for (auto& el : res) std::cout << el << '\n';
    
    return 0;
}


