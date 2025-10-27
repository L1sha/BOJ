#include <iostream>
#include <string>
#include <unordered_map>

int main () {
    
    int T; std::cin >> T;
    while (T--) {
        
        std::string s;
        std::unordered_map<std::string, int> map;
        int N; std::cin >> N;
        while (N--) {
            
            std::cin >> s >> s;
            if (map.count(s)) map[s]++;
            else map[s] = 1;
        }
        
        int res = 1;
        
        for (auto it = map.begin(); it != map.end(); ++it) {
            
            res *= (it->second + 1);
        }
        
        std::cout << res - 1 << '\n';
    }
}