#include <iostream>
#include <string>

int main() {
    
    int N; std::cin >> N;
    int M; std::cin >> M;
    std::string s; std::cin >> s;
    
    int res = 0, cnt = -1;
    
    for (int idx = 0; idx < M; ++idx) {
        
        if (s[idx] == 'I') {
            
            cnt = 0;
        }
        else {
            
            if (cnt >= 0) {
                
                if (idx + 1 < M && s[idx + 1] == 'I') {
                    
                    idx++;
                    
                    if (++cnt == N) {
                        
                        cnt--;
                        res++;
                    }
                }
                else {
                    
                    cnt = -1;
                }
            }
        }
    }
    
    std::cout << res;
    
    return 0;
}