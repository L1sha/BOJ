#include "bits/stdc++.h"

constexpr int N_MAX = 500;

int N, M;

std::array<std::array<int, N_MAX>, N_MAX> map;
std::array<std::array<std::pair<int, int>, 3>, 19> tetro{{
   
   {{   // I mino
       {1, 0}, {2, 0}, {3, 0}
   }}, 
   {{
       {0, 1}, {0, 2}, {0, 3}
   }},
   {{   // O mino
       {1, 0}, {1, 1}, {0, 1}
   }},
   {{   // L, J mino
       {0, 1}, {0, 2}, {1, 2}
   }},
   {{
       {0, 1}, {0, 2}, {-1, 2}
   }},
   {{
       {0, 1}, {0, 2}, {1, 0}
   }},
   {{
       {0, 1}, {0, 2}, {-1, 0}
   }},
   {{
       {0, 1}, {1, 1}, {2, 1}
   }},
   {{
       {0, 1}, {-1, 1}, {-2, 1}
   }},
   {{
       {0, 1}, {1, 0}, {2, 0}
   }},
   {{
       {0, 1}, {-1, 0}, {-2, 0}
   }},
   {{   // Z, S mino
       {0, 1}, {1, 1}, {1, 2}
   }},
   {{
       {0, 1}, {-1, 1}, {-1, 2}
   }},
   {{
       {1, 0}, {1, -1}, {2, -1}
   }},
   {{
       {1, 0}, {1, 1}, {2, 1}
   }},
   {{   // T mino
       {-1, 0}, {0, -1}, {1, 0}
   }},
   {{
       {0, -1}, {1, 0}, {0, 1}
   }},
   {{
       {1, 0}, {0, 1}, {-1, 0}
   }},
   {{
       {0, 1}, {-1, 0}, {0, -1}
   }}
}};



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> M;
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            std::cin >> map[row][col];
        }
    }
}

void solve() {
    
    int res = 0, temp;
    
    for (int row = 0; row < N; ++row) {
        
        for (int col = 0; col < M; ++col) {
            
            for (const auto& next : tetro) {
                
                temp = map[row][col];
                
                for (const auto& [x, y] : next) {
                    
                    if (row + x < 0 || row + x >= N || col + y < 0 || col + y >= M) {
                        
                        temp = 0;
                        break;
                    }
                    
                    temp += map[row + x][col + y];
                }
                
                res = std::max(res, temp);
            }
        }
    }
    
    std::cout << res;
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}

