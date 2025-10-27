#include "bits/stdc++.h"


int N;


struct myTime{
    
    int start, end;
    
    bool operator<(const myTime& rhs){ return (this->end < rhs.end || (this->end == rhs.end && this->start < rhs.start)); }
};


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    std::vector<myTime> conferences(N);
    
    for (int idx = 0; idx < N; ++idx) std::cin >> conferences[idx].start >> conferences[idx].end;
    std::sort(conferences.begin(), conferences.end());
    
    int now = 0, idx = 0, res = 0;
    
    while (idx < N){
        
        if (now <= conferences[idx].start){
            
            now = conferences[idx].end;
            res++;
        }
        
        idx++;
    }
    
    std::cout << res;
    
    return 0;
}



