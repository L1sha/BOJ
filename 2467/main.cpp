#include "bits/stdc++.h"


int N;

std::vector<int> pos;
std::vector<int> neg;




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int temp;
    
    while (N--) { 
        
        std::cin >> temp;
        
        if (temp > 0) pos.push_back(temp);
        else neg.push_back(-temp);
    }
    
    std::sort(pos.begin(), pos.end());
    std::sort(neg.begin(), neg.end());
    
    int min = INT_MAX, res1, res2, temp1 = INT_MAX, temp2 = INT_MAX;
    
    for (auto& el : pos){
        
        auto it = std::lower_bound(neg.begin(), neg.end(), el);
        
        if (it != neg.end()) temp1 = (*it - el);
        if (it != neg.begin()) temp2 = (el - *(it - 1));
        
        if (temp1 < min){
            
            res1 = -(*it);
            res2 = el;
            min = temp1;
        }
        
        if (temp2 < min){
            
            res1 = -(*(it - 1));
            res2 = el;
            min = temp2;
        }
        
        temp1 = INT_MAX;
        temp2 = INT_MAX;
    }
    
    for (auto& el : neg){
        
        auto it = std::lower_bound(pos.begin(), pos.end(), el);
        
        if (it != pos.end()) temp1 = (*it - el);
        if (it != pos.begin()) temp2 = (el - *(it - 1));
        
        if (temp1 < min){
            
            res1 = -el;
            res2 = *it;
            min = temp1;
        }
        
        if (temp2 < min){
            
            res1 = el;
            res2 = *(it - 1);
            min = temp2;
        }
        
        temp1 = INT_MAX;
        temp2 = INT_MAX;
    }
    
    if (pos.size() >= 2 && pos[0] + pos[1] < min){
        
        res1 = pos[0];
        res2 = pos[1];
    }
    
    if (neg.size() >= 2 && neg[0] + neg[1] < min){
        
        res1 = -neg[1];
        res2 = -neg[0];
    }
    
    std::cout << res1 << ' ' << res2;
    
    
    return 0;
}


