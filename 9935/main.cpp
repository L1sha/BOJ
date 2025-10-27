#include "bits/stdc++.h"


int slength, blength, tempLength, leftestIdx;
long long temp, trigger;
const long long PRIME = 503, DIVIDER = 1'000'000'007;

std::string s, bomb;

std::array<long long, 37> POWER;
std::array<int, 1'000'002> rightIdx, leftIdx;




int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> s >> bomb;
    
    slength = s.size();
    blength = bomb.size();
    
    s = std::string(" ") + s;
    
    for (auto& el : bomb) trigger = (trigger * PRIME + el) % DIVIDER;
    
    POWER[0] = 1;
    for (int idx = 1; idx <= blength; ++idx) POWER[idx] = (POWER[idx - 1] * PRIME) % DIVIDER;
    
    for (int idx = 0; idx <= slength + 1; ++idx) {
        
        leftIdx[idx] = idx - 1;
        rightIdx[idx] = idx + 1;
    }
    
    for (int idx = 1; idx != slength + 1; idx = rightIdx[idx]) {
            
        temp = (temp * PRIME + s[idx]) % DIVIDER;
        
        if (tempLength < blength) tempLength++;
        else {
            
            temp = ((temp - POWER[blength] * s[leftestIdx]) % DIVIDER + DIVIDER) % DIVIDER;
            leftestIdx = rightIdx[leftestIdx];
        }
        
        if (tempLength == 1) leftestIdx = idx;
        
        while (temp == trigger) {
            
            leftIdx[rightIdx[idx]] = leftIdx[leftestIdx];
            rightIdx[leftIdx[leftestIdx]] = rightIdx[idx];
            
            idx = leftIdx[leftestIdx];
            temp = 0;
            tempLength = 0;
            while (leftIdx[leftestIdx] != 0 && tempLength < blength) {
                
                leftestIdx = leftIdx[leftestIdx];
                temp = (temp + s[leftestIdx] * POWER[tempLength]) % DIVIDER;
                tempLength++;
            }
        }
    }
    
    std::string res;
    
    for (int idx = 0; idx != slength + 1; idx = rightIdx[idx]) res += s[idx];
    
    if (res == " ") std::cout << "FRULA";
    else std::cout << std::string(res.begin() + 1, res.end());
    
    return 0;
}



