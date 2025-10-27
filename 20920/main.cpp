#include "bits/stdc++.h"


int N, M;
std::unordered_map<std::string, int> cnt;

struct myStr{
    
    std::string s;
    
    myStr(const std::string& str) : s(str) {}
    
    bool operator<(const myStr& rhs) const{
        
        if (cnt[this->s] > cnt[rhs.s]) return true;
        else if (cnt[this->s] < cnt[rhs.s]) return false;
        else {
            
            if (this->s.size() > rhs.s.size()) return true;
            else if (this->s.size() < rhs.s.size()) return false;
            else return this->s < rhs.s;
        }
    }
};

std::vector<myStr> set;

    

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    std::cin.ignore();
    
    std::string str;
    
    while (N--){
        
        std::getline(std::cin, str);
        
        if (str.size() >= M){
            
            if (cnt.count(str)) cnt[str]++;
            else{
                
                cnt[str] = 1;
                set.push_back(str);
            }
        }
    }
    
    std::sort(set.begin(), set.end());
    
    for (auto& el : set) std::cout << el.s << '\n';
    
    return 0;
}


