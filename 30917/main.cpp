#include "bits/stdc++.h"

constexpr int N_MAX = 10'000;

int N;

std::array<std::array<int, N_MAX + 1>, 2> ptr;


void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
}

int getNum(int cIdx, int curr) {
    
    if (ptr[cIdx][curr] == curr) return curr;
    else return ptr[cIdx][curr] = getNum(cIdx, ptr[cIdx][curr]);
}

void ptrDelete(int cIdx, int curr) {
    
    ptr[cIdx][getNum(cIdx, curr)] = (curr == N_MAX ? getNum(cIdx, 1) : getNum(cIdx, curr + 1));
}

void solve() {
    
    std::array<char, 2> AB = {'A', 'B'};
    int res = 0;
    
    for (int cIdx = 0; cIdx < 2; ++cIdx) {
        
        for (int idx = 0; idx <= N_MAX; ++idx) {
            
            ptr[cIdx][idx] = idx;
        }
    }
            
    
    for (int cIdx = 0; cIdx < 2; ++cIdx) {
        
        int input, flag = 0;
        
        for (int num, idx = 0; idx < N_MAX - 1; ++idx) {
            
            num = getNum(cIdx, rand() % N_MAX + 1);
            
            std::cout << "? " << AB[cIdx] << ' ' << num << std::endl;
            std::cin >> input;
            
            if (input) {
                
                res += num;
                flag = 1;
                break;
            }
            else {
                
                ptrDelete(cIdx, num);
            }
        }
        
        if (!flag) {
            
            res += getNum(cIdx, 1);
        }
    }
    
    std::cout << "! " << res << std::endl;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}