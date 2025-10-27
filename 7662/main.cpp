#include "bits/stdc++.h"

int T, K, N;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> T;
}

void solve() {
    
    while (T--) {
        
        std::cin >> K;
        
        char c;
        int totalCnt = 0;
        std::priority_queue<int> max;
        std::priority_queue<int, std::vector<int>, std::greater<int>> min;
        std::map<int, int> cnt;
        
        while (K--) {
            
            std::cin >> c >> N;
            
            if (c == 'I') {
                
                max.push(N);
                min.push(N);
                
                if (cnt.count(N)) cnt[N]++;
                else cnt[N] = 1;
                totalCnt++;
            }
            else {
                
                if (totalCnt) {
                    
                    if (N == 1) {
                        
                        while (cnt[max.top()] == 0) {
                            
                            max.pop();
                        }
                        
                        cnt[max.top()]--;
                        max.pop();
                    }
                    else {
                        
                        while (cnt[min.top()] == 0) {
                            
                            min.pop();
                        }
                        
                        cnt[min.top()]--;
                        min.pop();
                    }
                    
                    totalCnt--;
                }
            }
        }
        
        if (totalCnt) {
            
            while (cnt[max.top()] == 0) {
                
                max.pop();
            }
            
            while (cnt[min.top()] == 0) {
                
                min.pop();
            }
            
            std::cout << max.top() << ' ' << min.top() << '\n';
        }
        else {
            
            std::cout << "EMPTY\n";
        }
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

