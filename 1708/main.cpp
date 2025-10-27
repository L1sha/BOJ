#include "bits/stdc++.h"


using LLPair = std::pair<long long, long long>;

int N;

std::array<LLPair, 100'000> pts;



bool onSameLine(const LLPair& a, const LLPair& b) {
    
    return a.first * b.second - a.second * b.first == 0;
}

bool CCW(const LLPair& a, const LLPair& b) {
    
    long long judge = a.first * b.second - a.second * b.first;
    if (judge > 0) {
        
        return true;
    }
    else if (judge == 0) {
        
        return a.first * a.first + a.second * a.second > b.first * b.first + b.second * b.second;
    }
    
    return false;
}

bool CCW3(const LLPair& a, const LLPair& b, const LLPair& c) {
    
    return CCW({b.first - a.first, b.second - a.second}, {c.first - a.first, c.second - a.second});
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    std::pair<long long, long long> min = {40'001, 40'001};
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> pts[idx].first >> pts[idx].second;
        min = std::min(min, pts[idx]);
    }
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (pts[idx] == min) {
            
            pts[idx] = pts[N - 1];
            N--;
        }
        
        pts[idx].first -= min.first;
        pts[idx].second -= min.second;
    }
    
    std::sort(pts.begin(), pts.begin() + N, CCW);
    
    std::vector<int> s;
    int sz;
    
    for (int idx = 0; idx < N; ++idx) {
        
        if (!s.empty() && onSameLine(pts[s.back()], pts[idx])) {
            
            continue;
        }
        
        while ((sz = s.size()) >= 2) {
            
            if (!CCW3(pts[s[sz - 2]], pts[s[sz - 1]], pts[idx])) {
                
                s.pop_back();
            }
            else {
                
                break;
            }
        }
        
        s.push_back(idx);
    }
    
    std::cout << s.size() + 1;
    
    return 0;
}

