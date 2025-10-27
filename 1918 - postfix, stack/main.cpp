#include "bits/stdc++.h"


std::string str;



std::string postfix(std::string::iterator begin, std::string::iterator end){
    
    std::string res;
    std::stack<char> s;
    
    for (auto it = begin; it != end; ++it){
        
        if (*it == '(') {
            
            auto it2 = std::find(++it, end, ')');
            
            int cnt = std::count(it, it2, '(');
            while (cnt){
                
                auto temp = it2;
                for (int idx = 0; idx < cnt; ++idx){
                    
                    temp = std::find(++temp, end, ')');
                }
                
                cnt = std::count(it2, temp, '(');
                it2 = temp;
            }
            
            res += postfix(it, it2);
            it = it2;
            
            if (!s.empty()) if (s.top() == '*' || s.top() == '/') {
                
                res += s.top();
                s.pop();
            }
        }
        else if (*it == '*' || *it == '/') {
         
            s.push(*it); 
        }
        else if (*it == '+' || *it == '-') {
            
            if (!s.empty()) if (s.top() == '+' || s.top() == '-') {
                
                res += s.top();
                s.pop();
            }
            s.push(*it);
        }
        else {
            
            res += *it;
            if (!s.empty()) if (s.top() == '*' || s.top() == '/') {
                
                res += s.top();
                s.pop();
            }
        }
    }
    
    while (!s.empty()) {
        
        res += s.top();
        s.pop();
    }
    
    return res;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> str;
    
    std::cout << postfix(str.begin(), str.end());
    
    return 0;
}


